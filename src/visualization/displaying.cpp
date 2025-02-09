#include <visualization/displaying.h>

// GLOBAL VARIABLES
// Gradient Descent

std::vector<Eigen::MatrixXd> rotations;

float rotationXOptimization = 0.0;
float rotationYOptimization = 0.0;
float rotationZOptimization = 0.0;

// Flags
std::vector<polyscope::CurveNetwork *> FlagLines;
std::vector<polyscope::SurfaceMesh *> FlagPlanes;

float rotationXFlag = 0.0;
float rotationYFlag = 0.0;
float rotationZFlag = 0.0;

void showMeshes(const std::vector<std::string> &filepaths)
{
	polyscope::init();
	std::vector<std::string> mesh_names = loadMeshes(filepaths);
	polyscope::state::userCallback = [&]()
	{
		meshTab(mesh_names);
	};
	polyscope::show();
}

void meshTab(const std::vector<std::string> &mesh_names)
{
	if (ImGui::BeginTabBar("Tabs"))
	{
		for (const auto &mesh_name : mesh_names)
		{
			if (ImGui::BeginTabItem(mesh_name.c_str()))
			{

				ImGui::Dummy(ImVec2(0.0f, 10.0f)); // spacing

				static int selectedItem = 0;
				std::vector<std::string> items = {"Rotation", "Convexcombination", "Optimial Rotation"};

				ImGui::Text("Select a function:");
				if (ImGui::BeginCombo("Functions", items[selectedItem].c_str()))
				{
					for (int i = 0; i < items.size(); i++)
					{
						bool isSelected = (selectedItem == i);
						if (ImGui::Selectable(items[i].c_str(), isSelected))
						{
							selectedItem = i;
							resetMesh(mesh_name);
						}
						if (isSelected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}

				ImGui::Dummy(ImVec2(0.0f, 20.0f)); // spacing

				switch (selectedItem)
				{
				case 0:
					rotationSlider(mesh_name);
					break;
				case 1:
					convexCombination(mesh_name);
					break;
				case 2:
					optimalRotationOnManifold(mesh_name);
					break;
				default:
					break;
				}

				ImGui::EndTabItem();
			}
		}

		if (ImGui::BeginTabItem("Display Flags"))
		{
			displayFlags();
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}

void rotationSlider(std::string mesh_name)
{

	MeshData &meshData = Meshes[mesh_name];
	polyscope::SurfaceMesh *mesh = polyscope::getSurfaceMesh(mesh_name);

	// Rotation around X-Axis
	ImGui::SliderFloat("Rotation Angle (X)", &meshData.rotationX, -180.0f, 180.0f);
	Eigen::MatrixXd rotatedVerticesX = rotateViaXAxis(meshData.vertices, degreesToRadians(meshData.rotationX));

	// Rotation around Y-Axis
	ImGui::SliderFloat("Rotation Angle (Y)", &meshData.rotationY, -180.0f, 180.0f);
	Eigen::MatrixXd rotatedVerticesY = rotateViaYAxis(rotatedVerticesX, degreesToRadians(meshData.rotationY));

	// Rotation around Z-Axis
	ImGui::SliderFloat("Rotation Angle (Z)", &meshData.rotationZ, -180.0f, 180.0f);
	Eigen::MatrixXd rotatedVerticesZ = rotateViaZAxis(rotatedVerticesY, degreesToRadians(meshData.rotationZ));

	mesh->updateVertexPositions(rotatedVerticesZ);
}

void convexCombination(std::string mesh_name)
{
	MeshData &meshData = Meshes[mesh_name];
	polyscope::SurfaceMesh *mesh = polyscope::getSurfaceMesh(mesh_name);

	ImGui::SliderFloat("Rotation Angle (X)", &meshData.rotationX, -180.0f, 180.0f);
	ImGui::SliderFloat("Rotation Angle (Y)", &meshData.rotationY, -180.0f, 180.0f);
	ImGui::SliderFloat("Rotation Angle (Z)", &meshData.rotationZ, -180.0f, 180.0f);

	ImGui::InputFloat("Scaling X", &meshData.scaleX, 0.05f, 0.5f, "%.2f");
	ImGui::InputFloat("Scaling Y", &meshData.scaleY, 0.05f, 0.5f, "%.2f");
	ImGui::InputFloat("Scaling Z", &meshData.scaleZ, 0.05f, 0.5f, "%.2f");

	ImGui::Dummy(ImVec2(0.0f, 20.0f));

	ImGui::BeginDisabled(std::abs((meshData.scaleX + meshData.scaleY + meshData.scaleZ) - 1.0f) > 1e-6);

	if (ImGui::Button(std::format("Apply ConvexCombinataion", mesh_name).c_str()))
	{

		Eigen::MatrixXd convex = convexCombinationXY(
			meshData.vertices,
			meshData.rotationX,
			meshData.rotationY,
			meshData.scaleX);

		mesh->updateVertexPositions(convex);
	}
	ImGui::SameLine();
	if (ImGui::Button("Apply Normalized ConvexCombination"))
	{

		Eigen::MatrixXd convex = convexCombinationOrthoXY(
			meshData.vertices,
			meshData.rotationX,
			meshData.rotationY,
			meshData.scaleX);

		mesh->updateVertexPositions(convex);
	}

	ImGui::EndDisabled();
}

void optimalRotationOnManifold(std::string mesh_name)
{
	MeshData &meshData = Meshes[mesh_name];
	polyscope::SurfaceMesh *mesh = polyscope::getSurfaceMesh(mesh_name);

	ImGui::Text("Amount of Rotations: %ld", rotations.size());

	ImGui::SliderFloat("Rotation Angle (X)", &rotationXOptimization, -180.0f, 180.0f);
	ImGui::SliderFloat("Rotation Angle (Y)", &rotationYOptimization, -180.0f, 180.0f);
	ImGui::SliderFloat("Rotation Angle (Z)", &rotationZOptimization, -180.0f, 180.0f);

	if (ImGui::Button("Reset Rotations"))
	{
		rotations.clear();
	}

	ImGui::SameLine();
	if (ImGui::Button("Add Rotation"))
	{
		Eigen::Matrix3d rotation = rotationMatrix(
			degreesToRadians(rotationXOptimization),
			degreesToRadians(rotationYOptimization),
			degreesToRadians(rotationZOptimization));

		rotations.push_back(rotation);
		FlagLines.push_back(displayLineFromMatrix(rotation, rotations.size()));
		FlagPlanes.push_back(displayPlaneFromMatrix(rotation, rotations.size()));
	}

	if (ImGui::Button("Generate Random Rotations"))
	{
		addRandomRotations(rotations, 1);
	}

	if (ImGui::Button("Optimize"))
	{
		RotationOptimizer optimizer(rotations, 1, 1000, 1e-6);
		Eigen::MatrixXd initialGuess = Eigen::MatrixXd::Identity(3, 3);
		Eigen::MatrixXd optimalRotation = optimizer.optimizeOnManifold(
			initialGuess,
			squaredChordalDistance,
			squaredChordalDistanceGradient);

		Eigen::MatrixXd rotated = meshData.vertices * optimalRotation;
		mesh->updateVertexPositions(rotated);
	}

	if (ImGui::Button("Optimize Flag"))
	{

		RotationOptimizer optimizer(rotations, 1, 1000, 1e-6);
		Eigen::MatrixXd initialGuess = Eigen::MatrixXd::Identity(3, 3);
		Eigen::MatrixXd optimalRotation = optimizer.optimizeOnFlag(
			initialGuess,
			squaredChordalDistanceFlag,
			squaredChordalDistanceGradientFlag);
	}
}

void displayFlags()
{
	ImGui::SliderFloat("Rotation Angle (X)", &rotationXFlag, -180.0f, 180.0f);
	ImGui::SliderFloat("Rotation Angle (Y)", &rotationYFlag, -180.0f, 180.0f);
	ImGui::SliderFloat("Rotation Angle (Z)", &rotationZFlag, -180.0f, 180.0f);

	Eigen::Matrix3d rotation = rotationMatrix(
		degreesToRadians(rotationXFlag),
		degreesToRadians(rotationYFlag),
		degreesToRadians(rotationZFlag));

	for (int i = 0; i < FlagLines.size(); ++i)
	{
		FlagLines[i]->setEnabled(true);
		FlagPlanes[i]->setEnabled(true);
	}

	if (ImGui::Button("Reset Rotations"))
	{
		removeDisplayedFlags(rotations, FlagLines, FlagPlanes);
		removeDisplayedFlag("optimal line", "optimal plane");
	}
	ImGui::SameLine();
	if (ImGui::Button("Add Rotation"))
	{
		rotations.push_back(rotation);
		FlagLines.push_back(displayLineFromMatrix(rotation, rotations.size()));
		FlagPlanes.push_back(displayPlaneFromMatrix(rotation, rotations.size()));
	}

	if (ImGui::Button("Generate Random Rotations"))
	{
		addRandomRotations(rotations, 1);
	}

	if (ImGui::Button("Optimize"))
	{
		removeDisplayedFlag("optimal line", "optimal plane");

		RotationOptimizer optimizer(rotations, 1, 1000, 1e-6);
		Eigen::MatrixXd initialGuess = Eigen::MatrixXd::Identity(3, 3);
		Eigen::MatrixXd optimalRotation = optimizer.optimizeOnFlag(
			initialGuess,
			squaredChordalDistanceFlag,
			squaredChordalDistanceGradientFlag);

		auto [points, edges] = getLinePointsAndEdges(optimalRotation);
		auto [psVertices, faces] = getPlanePointsAndFaces(optimalRotation);

		auto *line = polyscope::registerCurveNetwork("optimal line", points, edges);
		line->setRadius(0.01);
		auto *plane = polyscope::registerSurfaceMesh("optimal plane", psVertices, faces);
	}

	auto *new_line = displayLineFromMatrix(rotation, 0, true);
	auto *new_plane = displayPlaneFromMatrix(rotation, 0, true);
}
#include <visualization/displaying.h>

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
				std::vector<std::string> items = {"Rotation", "Convexcombination"};

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
				default:
					break;
				}

				ImGui::EndTabItem();
			}
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

	ImGui::Dummy(ImVec2(0.0f, 20.0f)); // spacing

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
	if (ImGui::Button(std::format("Apply Normalized ConvexCombination", mesh_name).c_str()))
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

void resetMesh(std::string mesh_name)
{
	MeshData &meshData = Meshes[mesh_name];
	polyscope::SurfaceMesh *mesh = polyscope::getSurfaceMesh(mesh_name);

	resetMeshProperties(mesh_name);

	mesh->updateVertexPositions(meshData.vertices);
}
//
// Created by dj on 13/07/2025.
//

#pragma once
#include "imgui.h"

struct WorldGameObjectsEditor {
	std::shared_ptr<GameObject> VisibleNode = NULL;

	void draw() {
		ImGui::Begin("World Editor");

		// Left side (all the objects)
		ImGui::SeparatorText("Object Editor");
		ImGui::BeginChild("LeftPanel", ImVec2(300, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX);
		ImGui::SeparatorText("All Objects");

		if (ImGui::BeginTable("##bg", 1, ImGuiTableFlags_RowBg)) {
			for (std::shared_ptr<GameObject> node: GameConstants::world.getObjects()) DrawTreeNode(node);
			ImGui::EndTable();
		}

		ImGui::EndChild();


		// Right side (the object config)
		ImGui::SameLine();
		ImGui::BeginChild("RightPanel", ImVec2(0, 0), ImGuiChildFlags_Borders); // width = remaining space
		ImGui::SeparatorText("Demo Properties");

		if (std::shared_ptr<GameObject> node = VisibleNode) {
			ImGui::SeparatorText("Properties");
			ImGui::Text("Read-Only Properties");
			ImGui::Text("Id: 0x"+node->id);
			ImGui::Text(("Type: "+node->type).c_str());

			ImGui::Text("Editable Properties");
			ImGui::Checkbox("Collidable", &node->collidable);
			ImGui::Spacing();

			ImGui::SeparatorText("Position");

			float offset = 0.5f;
			ImGui::SliderFloat("X", &node->position.x, node->position.x-offset, node->position.x+offset);
			ImGui::SliderFloat("Y", &node->position.y, node->position.y-offset, node->position.y+offset);
			ImGui::Spacing();
		}

		ImGui::EndChild();

		ImGui::End();
	}

	void DrawTreeNode(const std::shared_ptr<GameObject> &node) {
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::PushID(node->id);
		ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_None;
		bool selected = (node == VisibleNode);
		if (selected)
			tree_flags |= ImGuiTreeNodeFlags_Selected;
		if (ImGui::Selectable((node->type + " (0x" + std::to_string(node->id)+")").c_str(), selected, ImGuiSelectableFlags_SpanAllColumns))
			VisibleNode = node;
		ImGui::PopID();
	}
};

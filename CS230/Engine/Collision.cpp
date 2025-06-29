
#pragma once
#include "Collision.h"

CS230::RectCollision::RectCollision(Math::irect boundary, GameObject* object) : boundary(boundary), object(object) {

}

void CS230::RectCollision::Draw(Math::TransformationMatrix display_matrix) {
    const double render_height = rlGetFramebufferHeight();

    Math::rect world_boundary = WorldBoundary();

    Math::vec2 bottom_left = display_matrix * Math::vec2{ world_boundary.Left(), world_boundary.Bottom() };
    Math::vec2 bottom_right = display_matrix * Math::vec2{ world_boundary.Right(), world_boundary.Bottom() };
    Math::vec2 top_left = display_matrix * Math::vec2{ world_boundary.Left(), world_boundary.Top() };
    Math::vec2 top_right = display_matrix * Math::vec2{ world_boundary.Right(), world_boundary.Top() };

    bottom_left.y = bottom_left.y * -1 + render_height;
    bottom_right.y = bottom_right.y * -1 + render_height;
    top_left.y = top_left.y * -1 + render_height;
    top_right.y = top_right.y * -1 + render_height;

    DrawLine(int(top_left.x), int(top_left.y), int(top_right.x), int(top_right.y), WHITE);
    DrawLine(int(bottom_right.x), int(bottom_right.y), int(top_right.x), int(top_right.y), WHITE);
    DrawLine(int(bottom_right.x), int(bottom_right.y), int(bottom_left.x), int(bottom_left.y), WHITE);
    DrawLine(int(top_left.x), int(top_left.y), int(bottom_left.x), int(bottom_left.y), WHITE);
}

bool CS230::RectCollision::IsCollidingWith(GameObject* other_object) {
    Collision* other_collider = other_object->GetGOComponent<Collision>();

    if (other_collider == nullptr) {
        //Engine::GetLogger().LogError("No collision component found");
        return false;
    }
    if (other_collider->Shape() != CollisionShape::Rect) {
        Engine::GetLogger().LogError("Rect vs unsupported type");
        return false;
    }

    Math::rect rectangle_1 = WorldBoundary();
    Math::rect rectangle_2 = dynamic_cast<RectCollision*>(other_collider)->WorldBoundary();

    if (rectangle_1.Left() < rectangle_2.Right() && rectangle_1.Right() > rectangle_2.Left() && rectangle_1.Bottom() < rectangle_2.Top() && rectangle_1.Top() > rectangle_2.Bottom()) {
        return true;
    }
    return false;
}

bool CS230::RectCollision::IsCollidingWith(Math::vec2 point) {
    Math::rect rectangle = WorldBoundary();

    if (rectangle.Left() <= point.x && rectangle.Right() >= point.x && rectangle.Bottom() <= point.y && rectangle.Top() >= point.y) {
        return true;
    }
    return false;
}

Math::rect CS230::RectCollision::WorldBoundary() {
    return {
        object->GetMatrix() * static_cast<Math::vec2>(boundary.point_1),
        object->GetMatrix() * static_cast<Math::vec2>(boundary.point_2)
    };
}

// Rect

CS230::CircleCollision::CircleCollision(double radius, GameObject* object) : radius(radius), object(object) {

}

void CS230::CircleCollision::Draw(Math::TransformationMatrix display_matrix) {
    const double render_height = rlGetFramebufferHeight();
    Math::vec2 transformed_position = display_matrix * object->GetPosition();
    transformed_position.y = transformed_position.y * -1 + render_height;
    const int num_segments = 36;
    Math::vec2 previous_vertex;
    for (int i = 0; i <= num_segments + 1; i++) {
        double theta = 2.0 * PI * static_cast<double>(i) / static_cast<double>(num_segments);
        Math::vec2 vertex = {
            transformed_position.x + GetRadius() * std::cos(theta),
            transformed_position.y + GetRadius() * std::sin(theta)
        };
        if (i > 0) {
            DrawLine(int(vertex.x), int(vertex.y), int(previous_vertex.x), int(previous_vertex.y), WHITE);
        }
        previous_vertex = vertex;
    }
}

bool CS230::CircleCollision::IsCollidingWith(GameObject* other_object) {
    Collision* other_collider = other_object->GetGOComponent<Collision>();

    if (other_collider == nullptr) {
        //Engine::GetLogger().LogError("No collision component found");
        return false;
    }
    if (other_collider->Shape() != CollisionShape::Circle) {
        Engine::GetLogger().LogError("Circle vs unsupported type");
        return false;
    }

    double circle_1 = GetRadius();
    double circle_2 = dynamic_cast<CircleCollision*>(other_collider)->GetRadius();

    Math::vec2 pos_1 = object->GetPosition();
    Math::vec2 pos_2 = other_object->GetPosition();
    double diff_x = pos_1.x - pos_2.x;
    double diff_y = pos_1.y - pos_2.y;

    if (diff_x * diff_x + diff_y * diff_y < (circle_1 + circle_2) * (circle_1 + circle_2)) {
        return true;
    }
    return false;
}

bool CS230::CircleCollision::IsCollidingWith(Math::vec2 point) {
    Math::vec2 pos = object->GetPosition();
    double circle = GetRadius();

    double diff_x = pos.x - point.x;
    double diff_y = pos.y - point.y;

    if (diff_x * diff_x + diff_y * diff_y <= circle * circle) {
        return true;
    }
    return false;
}

double CS230::CircleCollision::GetRadius() {
    return radius * (object->GetScale().x + object->GetScale().y) / 2.0;
}
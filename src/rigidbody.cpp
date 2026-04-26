#include "rigidbody.h"

void RigidBody::applyForce(const glm::vec3& f) {
    force += f;
}

void RigidBody::integrate(glm::vec3& position, float dt) {
    glm::vec3 acceleration = force / mass;

    if (useGravity) {
        acceleration += glm::vec3(0.0f, -9.8f, 0.0f);
    }

    velocity += acceleration * dt;
    velocity *= frictionDamping;
    position += velocity * dt;

    float bounciness = 0.5f; 
    if (position.y < 0.0f) {
        position.y = 0.0f;
        velocity.y = -velocity.y * bounciness;
    }

    force = glm::vec3(0.0f);
} 
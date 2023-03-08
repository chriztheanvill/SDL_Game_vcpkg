#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "./Vector2D.h"
#include "../Core/Node.h"

class RigidBody : public Node
{
  public:
	RigidBody(Node* parent = nullptr)
		: Node(parent, "RigidBody")
	{
		SetName("RigidBody::Player");
		Logger::Debug(LogType::Log, "RigidBody::Constructor", GetName( ));
	}
	// RigidBody( ) = default;
	// RigidBody(const RigidBody& other); // Copy
	// RigidBody(RigidBody&& other) noexcept; // Move
	// RigidBody& operator=(const RigidBody& other); // Copy Operator
	// RigidBody& operator=(RigidBody&& other) noexcept; // Move Operator

	~RigidBody( ) override
	{
		Logger::Debug(LogType::Log, "~RigidBody::Destructor", GetName( ));
	}

	void SetMass(const float& m) { mMass = m; }
	void SetGravity(const float& g) { mGravity = g; }

	void ApplyForce(const Vector2D& v) { mForce = v; }
	void ApplyForceX(const float& v) { mForce.SetX(v); }
	void ApplyForceY(const float& v) { mForce.SetY(v); }
	void UnsetForce( ) { mForce = Vector2D::Zero( ); }
	void UnsetForceX( ) { mForce.SetX(0); }
	void UnsetForceY( ) { mForce.SetY(0); }

	void ApplyFriction(const Vector2D& v) { mFriction = v; }
	void UnsetFriction( ) { mFriction = Vector2D::Zero( ); }

	void Update(const float& deltaTime)
	{
		mAcceleration.SetX((mForce.GetX( ) + mFriction.GetX( )) / mMass);
		mAcceleration.SetY(mGravity + mForce.GetY( ) / mMass);
		mVelocity = mAcceleration * deltaTime;
		// mVelocity = (mAcceleration * deltaTime) * mTime;
		mPosition = mVelocity * deltaTime;
	}

	const float& Mass( ) const { return mMass; }
	const Vector2D& Pos( ) const { return mPosition; }
	const Vector2D& Velocity( ) const { return mVelocity; }
	const Vector2D& Acceleration( ) const { return mAcceleration; }

  private:
	float mMass { 1 };
	float mGravity { 9.8 };
	int16_t mTime { 10 };

	Vector2D mForce { 0, 0 };
	Vector2D mFriction { 0, 0 };

	Vector2D mPosition { 0, 0 };
	Vector2D mVelocity { 0, 0 };
	Vector2D mAcceleration { 0, 0 };
};

#endif	 // RIGIDBODY_H
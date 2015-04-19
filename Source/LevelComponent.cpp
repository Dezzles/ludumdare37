#include "LevelComponent.hpp"
#include "PuzzleComponent.hpp"
#include "EnemyComponent.hpp"
#include "Bubblewrap/Events.hpp"
using namespace Math;

LevelComponent::LevelComponent()
{
	TimeToSpawn_ = 0;
}

void LevelComponent::Initialise( Json::Value Params )
{
	Component::Initialise( Params );
	
	REQUIRED_LOAD( Float, SpawnX, spawnX );
	REQUIRED_LOAD( Float, SpawnY, spawnY );
	REQUIRED_LOAD( Float, SpawnRate, spawnRate );
	REQUIRED_LOAD( Float, PuzzleGap, puzzleGap );
	REQUIRED_LOAD( Float, EnemySpeed, enemySpeed );
	TimeToSpawn_ = SpawnRate_;
}


void LevelComponent::Copy( LevelComponent* Target, LevelComponent* Base )
{
	Component::Copy( Target, Base );
	NAIVE_COPY( SpawnX );
	NAIVE_COPY( SpawnY );
	NAIVE_COPY( SpawnRate );
	NAIVE_COPY( TimeToSpawn );
	NAIVE_COPY( PuzzleGap );
	NAIVE_COPY( EnemySpeed );
}

void LevelComponent::OnAttach()
{
}

void LevelComponent::Update( float dt )
{
	TimeToSpawn_ -= dt;
	SetPuzzleCoordinates();
	if ( TimeToSpawn_ < 0.0f )
	{
		TimeToSpawn_ += SpawnRate_;
		Base::Entity* enemy = dynamic_cast<Base::Entity*>( GetRegister().LoadObject( "basics:EnemyEntity", GetParentEntity() ) );
		enemy->SetLocalPosition( Vector3f( SpawnX_, SpawnY_, 0.0f ) );

		Base::Entity* puzzle = dynamic_cast< Base::Entity* > ( GetRegister().LoadObject("basics:PuzzleEntity", GetParentEntity( ) ) );
		puzzle->SetLocalPosition(Math::Vector3f( -100, PuzzleGap_, 0));

		PuzzleComponent* puzzleComponent = puzzle->GetComponentsByType<PuzzleComponent>()[ 0 ];
		puzzleComponent->SetEnemyObject( enemy->GetComponentsByType<EnemyComponent>()[ 0 ] );
		puzzleComponent->SetLevelObject( this );
		Puzzles_.push_back( puzzle );
		SetPuzzleCoordinates();
	}
}

void LevelComponent::RemovePuzzle( Base::Entity* Puzzle )
{
	for ( int Idx = 0; Idx < Puzzles_.size(); ++Idx )
	{
		if ( Puzzles_[ Idx ] == Puzzle )
		{
			Puzzles_.erase( Puzzles_.begin() + Idx );
			return;
		}
	}
	SetPuzzleCoordinates();
}

void LevelComponent::SetPuzzleCoordinates()
{
	float right = 800 - PuzzleGap_;
	float m = 800;
	for ( int Idx = 0; Idx < Puzzles_.size(); ++Idx )
	{
		PuzzleComponent* comp = Puzzles_[ Idx ]->GetComponentsByType< PuzzleComponent >()[ 0 ];
		comp->SetMaxPosition( m - comp->GetRenderWidth() );
		float left = right - comp->GetRenderWidth();

		comp->SetTargetXCoord( left );
		// Puzzles_[ Idx ]->SetLocalPosition( Math::Vector3f( left, PuzzleGap_, 0.0f ) );
		m = Puzzles_[ Idx ]->LocalPosition().X() - PuzzleGap_;
		right = left - PuzzleGap_;
	}

}
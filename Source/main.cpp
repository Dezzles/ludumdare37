#include "Bubblewrap/Bubblewrap.hpp"
#include "PuzzleComponent.hpp"
#include "LevelComponent.hpp"
#include "EnemyComponent.hpp"
#include "Bubblewrap/Registers/BubblewrapRegister.hpp"
#include "Bubblewrap/Registers/SfmlRegisters.hpp"
#include "Bubblewrap/Math/Matrix3.hpp"
#include "BackgroundComponent.hpp"
int main()
{
	Bubblewrap::Game::GameSettings settings;
	settings.WindowCount_ = 1;
	settings.WindowSettings_ = new Bubblewrap::Render::Window::WindowSettings[ 1 ];
	settings.WindowSettings_[ 0 ].Width_ = 800;
	settings.WindowSettings_[ 0 ].Height_ = 600;
	settings.WindowSettings_[ 0 ].Title_ = "Ludum Dare #32 - Conversion";
	settings.WindowSettings_[ 0 ].Name_ = "Main";
	settings.WindowSettings_[ 0 ].Colour_ = Bubblewrap::Render::Colour( 0, 0, 1.0f );
	Bubblewrap::Logs::StaticLog::Instance()->SetLogLevel( Bubblewrap::Logs::StaticLog::WARNING );
	settings.Registers_.push_back( Bubblewrap::Registers::SfmlRegisters::RegisterUtilities );
	settings.Registers_.push_back( Bubblewrap::Registers::SfmlRegisters::RegisterGraphics );
	settings.Registers_.push_back( Bubblewrap::Registers::SfmlRegisters::RegisterAudio );
	settings.Resources_.push_back( "textures" );
	settings.TypeRegistration_ = ( [ ]( Bubblewrap::Base::ObjectRegister* Register )
	{
		Register->RegisterCreator( "BackgroundComponent", BackgroundComponent::Create, BackgroundComponent::CopyDef );
		Register->RegisterCreator( "PuzzleComponent", PuzzleComponent::Create, PuzzleComponent::CopyDef );
		Register->RegisterCreator( "LevelComponent", LevelComponent::Create, LevelComponent::CopyDef );
		Register->RegisterCreator( "EnemyComponent", EnemyComponent::Create, EnemyComponent::CopyDef );
	} );
	settings.Packages_.push_back( "basics.json" );
	settings.BaseObject_ = "basics:LevelEntity";
	Bubblewrap::Game::Game Game;
	Game.Run( settings );
}
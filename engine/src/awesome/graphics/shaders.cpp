#include "shaders.h"

namespace awesome
{
	// shader names

	const std::string Shaders::names::ColorShader = "color";
	const std::string Shaders::names::TextureShader = "texture";
	const std::string Shaders::names::CroppedTextureShader = "cropped_texture";

	// shader param names

	const std::string Shaders::params::ModelViewProjectionMatrix = "u_ModelViewProjectionMatrix";
	const std::string Shaders::params::ViewProjectionMatrix = "u_ViewProjectionMatrix";
	const std::string Shaders::params::ModelTransformMatrix = "u_Transform";
	const std::string Shaders::params::Color = "u_Color";
	const std::string Shaders::params::Texture = "u_Texture";
	const std::string Shaders::params::TextureCropping = "u_TextureCropping";
	
}
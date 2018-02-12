#version 440

// *********************************
// Define the output colour for the shader here
uniform vec4 colour;
layout (location = 0) in vec4 colour_in;
//uniform vec4 colour;

//glUniformMatrix4fv (eff . get_uniform_location ("MVP") , 1 , GL_FALSE , value_ptr ( MVP )) ; 
// *********************************

// Outgoing colour for the shader
layout(location = 0) out vec4 out_colour;

void main() {
  // *********************************
  // Set outgoing colour
  //uniform vec4 colour;
  out_colour = colour;
  // *********************************
}
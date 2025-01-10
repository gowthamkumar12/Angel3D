#type vertex
#version 330 core

layout(location = 0) in vec3  a_Position;
layout(location = 1) in vec4  a_Color;
layout(location = 2) in vec2  a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;

uniform mat4 u_ViewProjectionMatrix;

out vec4  v_Color;
out vec2  v_TexCoord;
out float v_TexIndex;
out float v_TilingFactor;

void main()
{
  v_Color        = a_Color;
  v_TexCoord     = a_TexCoord;
	v_TexIndex     = a_TexIndex;
	v_TilingFactor = a_TilingFactor;
  gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_Textures[32];

in vec4  v_Color;
in vec2  v_TexCoord;
in float v_TexIndex;
in float v_TilingFactor;

void main()
{
  vec4 textureColor = v_Color;
  switch(int(v_TexIndex))
  {
    case 0  : textureColor *= texture(u_Textures[0], v_TexCoord * v_TilingFactor); break;
    case 1  : textureColor *= texture(u_Textures[1], v_TexCoord * v_TilingFactor); break;
    case 2  : textureColor *= texture(u_Textures[2], v_TexCoord * v_TilingFactor); break;
    case 3  : textureColor *= texture(u_Textures[3], v_TexCoord * v_TilingFactor); break;
    case 4  : textureColor *= texture(u_Textures[4], v_TexCoord * v_TilingFactor); break;
    case 5  : textureColor *= texture(u_Textures[5], v_TexCoord * v_TilingFactor); break;
    case 6  : textureColor *= texture(u_Textures[6], v_TexCoord * v_TilingFactor); break;
    case 7  : textureColor *= texture(u_Textures[7], v_TexCoord * v_TilingFactor); break;
    case 8  : textureColor *= texture(u_Textures[8], v_TexCoord * v_TilingFactor); break;
    case 9  : textureColor *= texture(u_Textures[9], v_TexCoord * v_TilingFactor); break;
    case 10 : textureColor *= texture(u_Textures[10], v_TexCoord * v_TilingFactor); break;
    case 11 : textureColor *= texture(u_Textures[11], v_TexCoord * v_TilingFactor); break;
    case 12 : textureColor *= texture(u_Textures[12], v_TexCoord * v_TilingFactor); break;
    case 13 : textureColor *= texture(u_Textures[13], v_TexCoord * v_TilingFactor); break;
    case 14 : textureColor *= texture(u_Textures[14], v_TexCoord * v_TilingFactor); break;
    case 15 : textureColor *= texture(u_Textures[15], v_TexCoord * v_TilingFactor); break;
    case 16 : textureColor *= texture(u_Textures[16], v_TexCoord * v_TilingFactor); break;
    case 17 : textureColor *= texture(u_Textures[17], v_TexCoord * v_TilingFactor); break;
    case 18 : textureColor *= texture(u_Textures[18], v_TexCoord * v_TilingFactor); break;
    case 19 : textureColor *= texture(u_Textures[19], v_TexCoord * v_TilingFactor); break;
    case 20 : textureColor *= texture(u_Textures[20], v_TexCoord * v_TilingFactor); break;
    case 21 : textureColor *= texture(u_Textures[21], v_TexCoord * v_TilingFactor); break;
    case 22 : textureColor *= texture(u_Textures[22], v_TexCoord * v_TilingFactor); break;
    case 23 : textureColor *= texture(u_Textures[23], v_TexCoord * v_TilingFactor); break;
    case 24 : textureColor *= texture(u_Textures[24], v_TexCoord * v_TilingFactor); break;
    case 25 : textureColor *= texture(u_Textures[25], v_TexCoord * v_TilingFactor); break;
    case 26 : textureColor *= texture(u_Textures[26], v_TexCoord * v_TilingFactor); break;
    case 27 : textureColor *= texture(u_Textures[27], v_TexCoord * v_TilingFactor); break;
    case 28 : textureColor *= texture(u_Textures[28], v_TexCoord * v_TilingFactor); break;
    case 29 : textureColor *= texture(u_Textures[29], v_TexCoord * v_TilingFactor); break;
    case 30 : textureColor *= texture(u_Textures[30], v_TexCoord * v_TilingFactor); break;
    case 31 : textureColor *= texture(u_Textures[31], v_TexCoord * v_TilingFactor); break;
    default : break;
  }
  color = textureColor;
}
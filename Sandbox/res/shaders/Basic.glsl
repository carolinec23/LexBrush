#shader vertex#version 330 corelayout(location = 0) in vec4 color;layout(location = 1) in vec2 position;layout(location = 2) in vec2 texCoord;out vec4 v_Color;out vec2 v_TexCoord;uniform mat4 u_MVP;void main(){	gl_Position = u_MVP * vec4(position.xy,0,1);	v_TexCoord = texCoord;	v_Color = color;};#shader fragment#version 330 corelayout(location = 0) out vec4 color;in vec4 v_Color;in vec2 v_TexCoord;uniform sampler2D u_Texture; void main(){	vec4 texColor = texture(u_Texture, v_TexCoord) * v_Color;	color = texColor;};
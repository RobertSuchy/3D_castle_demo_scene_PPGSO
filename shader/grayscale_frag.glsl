#version 330

uniform sampler2D Texture;

uniform float Transparency;

uniform vec2 TextureOffset;

in vec2 texCoord;

out vec4 FragmentColor;

void main() {
    vec4 color = texture2D(Texture, texCoord);
    float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));

    vec3 grayscale = vec3(gray);

    FragmentColor = vec4(grayscale, 1.0);
}

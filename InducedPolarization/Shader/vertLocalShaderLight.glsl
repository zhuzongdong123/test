
uniform vec3 uLightPos;//光源位置
uniform vec3 uViewPos;//相机位置

varying vec3 normal;
varying vec3 VerPosition;
varying vec4 verColor;

void main()
{
	normal = gl_NormalMatrix  * gl_Normal;
    VerPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
	verColor = gl_Color;

	gl_Position = ftransform();
}
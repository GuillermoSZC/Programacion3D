uniform mat4 mvp;
attribute vec3 vpos;
attribute vec3 vcolor;
varying vec3 fcolor;
attribute vec2 vtex;
varying vec2 ftex;

void main() {
	gl_Position = mvp * vec4(vpos, 1);
	fcolor = vcolor;
	ftex = vtex;
}
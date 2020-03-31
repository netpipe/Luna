// simple geometry shader

// these lines enable the geometry shader support.
#version 120
#extension GL_EXT_geometry_shader4 : enable
/*
varying in mat3 Rx1[3];
varying in vec4 tformed[3];
uniform vec3 windDir;
uniform float time;

float smooth(float x) {
	return x*x*(3.0-2.0*x);
}

float wind(float x) {
	return smooth(abs(fract(x+0.5)*2.0-1.0));
}

float MainWind(float x,float factor) {
	return (0.1+abs(sin(x*0.01021))*0.35+wind(x*0.2965)*0.5+wind(x*0.865)*0.5+sin(x*9.585)*0.09)*pow(factor,4.2)+sin((x+factor*0.35)*1.58845*windDir.y)*0.19*pow(factor,5.0);
}

float rotateWindDir(vec2 x) {
	return ((x.x+x.y)*cos(acos(windDir.z)-0.785549163)-(x.y-x.x)*sin(asin(windDir.x)+0.785549163))*0.04;
}

void main( void )
{
	if (centr[0].w<1.0)
		return;
	else {
	float copiesf = centr[0].w/6.28319;
	vec4 tmp;
	float ratio;
	for( int i = 0 ; i < gl_VerticesIn ; i++ )
	{
		gl_FrontColor  = gl_FrontColorIn[i];
		gl_Position    = vec4(tformed[i].xyz,1.0);
		gl_TexCoord[0] = gl_TexCoordIn[i][0];
		EmitVertex();
	}
	EndPrimitive();
	for (int j=1; j<centr[0].w; j++) {
		ratio = float(j)/copiesf;
		for( int i = 0 ; i < gl_VerticesIn ; i++ )
		{
			tmp = vec4(Rx1[0]*mat3(vec3(cos(ratio),-sin(ratio),0.0),vec3(sin(ratio),cos(ratio),0.0),vec3(0.0,0.0,1.0))*gl_PositionIn[i].xyz,gl_PositionIn[i].w);
			vec3 windOffset = vec3(windDir.x,0.0,windDir.z)*windDir.y*MainWind(time+rotateWindDir(tmp.xz+centr[0].xz),1.0-gl_TexCoordIn[i][0].y);
			windOffset = normalize(tmp.xyz+windOffset);
			tmp = gl_ModelViewProjectionMatrix*vec4(centr[0].xyz+length(tmp.xyz)*windOffset,tmp.w);
			gl_FrontColor.x  = clamp(exp2(-gl_Fog.density * length(tmp.xyz) * 1.442695), 0.0, 1.0);
			gl_FrontColor.gba  = gl_FrontColorIn[i].gba;
			gl_Position    = tmp;
			gl_TexCoord[0] = gl_TexCoordIn[i][0];
			EmitVertex();
		}
		EndPrimitive();
	}
	}
}
*/

void main( void )
{
	if (gl_FrontColorIn[0].y<0.9)
		return;
	else {
		for( int i = 0 ; i < gl_VerticesIn ; i++ )
		{
			gl_FrontColor  = gl_FrontColorIn[i];
			gl_Position    = gl_PositionIn[i];
			gl_TexCoord[0] = gl_TexCoordIn[i][0];
			EmitVertex();
		}
	}
}

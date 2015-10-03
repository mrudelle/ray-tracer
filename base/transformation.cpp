/* 
 * File:   transformation.h
 * Author: Matt
 *
 * Created on 10 February 2014, 12:30
 */
#include "include/transformation.h"
#include <string>
#include <cmath>

void Transformation::link(Transformation *obj)
{
  t_next = obj;
}

Transformation *Transformation::next(void)
{
  return t_next;
}

Transformation::Transformation() 
{
    A = 0.0;
    B = 0.0;
    C = 0.0;
    D = 0.0;
    E = 0.0;
    F = 0.0;
    G = 0.0;
    H = 0.0;
    I = 0.0;
    J = 0.0;
    K = 0.0;
    L = 0.0;
}

void Transformation::set(float a, float b, float c, float d,
                float e, float f, float g, float h,
                float i, float j, float k, float l) 
{
    A = a; 
    B = b; 
    C = c; 
    D = d; 
    E = e; 
    F = f; 
    G = g; 
    H = h; 
    I = i; 
    J = j; 
    K = k; 
    L = l;
}

void Transformation::rotationx(float alpha)
{
	A = 1.0;
    B = 0.0;
    C = 0.0;
    D = 0.0;
    E = 0.0;
    F = cos(alpha);
    G = -sin(alpha);
    H = 0.0;
    I = 0.0;
    J = sin(alpha);
    K = cos(alpha);
    L = 0.0;
}

void Transformation::rotationy(float alpha)
{
	A = cos(alpha);
    B = 0.0;
    C = sin(alpha);
    D = 0.0;
    E = 0.0;
    F = 1.0;
    G = 0.0;
    H = 0.0;
    I = -sin(alpha);
    J = 0.0;
    K = cos(alpha);
    L = 0.0;
}

void Transformation::rotationz(float alpha)
{
	A = cos(alpha);
    B = -sin(alpha);
    C = 0.0;
    D = 0.0;
    E = sin(alpha);
    F = cos(alpha);
    G = 0.0;
    H = 0.0;
    I = 0.0;
    J = 0.0;
    K = 1.0;
    L = 0.0;
}

void Transformation::translation(float x, float y, float z)
{
	A = 1.0;
    B = 0.0;
    C = 0.0;
    D = x;
    E = 0.0;
    F = 1.0;
    G = 0.0;
    H = y;
    I = 0.0;
    J = 0.0;
    K = 1.0;
    L = z;
}

void Transformation::scale(float x, float y, float z)
{
	A = x;
    B = 0.0;
    C = 0.0;
    D = 0.0;
    E = 0.0;
    F = y;
    G = 0.0;
    H = 0.0;
    I = 0.0;
    J = 0.0;
    K = z;
    L = 0.0;
}

void Transformation::identity()
{
    A = 1.0;
    B = 0.0;
    C = 0.0;
    D = 0.0;
    E = 0.0;
    F = 1.0;
    G = 0.0;
    H = 0.0;
    I = 0.0;
    J = 0.0;
    K = 1.0;
    L = 0.0;
}

Vertex Transformation::transform(Vertex v)
{
	Vertex va;
	va.set(
		v.x * A + v.y * B + v.z * C + v.w * D,
		v.x * E + v.y * F + v.z * G + v.w * H,
		v.x * I + v.y * J + v.z * K + v.w * L,
		v.w);
	return va;
}

Vector Transformation::transform(Vector v)
{
	Vector va;
	va.set(
		v.x * A + v.y * B + v.z * C,
		v.x * E + v.y * F + v.z * G,
		v.x * I + v.y * J + v.z * K);
	return va;
}

/*
	Compose this transformation with an new one
	this means that in the new transformation
	t will be performed after the base transformation
	So NewT = T * This
*/
Transformation Transformation::composeWith(const Transformation t)
{
	Transformation ta;
	ta.set(
		t.A * A + t.B * E + t.C * I + t.D * 0 ,
		t.A * B + t.B * F + t.C * J + t.D * 0 ,
		t.A * C + t.B * G + t.C * K + t.D * 0 ,
		t.A * D + t.B * H + t.C * L + t.D * 1 ,
		t.E * A + t.F * E + t.G * I + t.H * 0 ,
		t.E * B + t.F * F + t.G * J + t.H * 0 ,
		t.E * C + t.F * G + t.G * K + t.H * 0 ,
		t.E * D + t.F * H + t.G * L + t.H * 1 ,
		t.I * A + t.J * E + t.K * I + t.L * 0 ,
		t.I * B + t.J * F + t.K * J + t.L * 0 ,
		t.I * C + t.J * G + t.K * K + t.L * 0 ,
		t.I * D + t.J * H + t.K * L + t.L * 1
		);
	return ta;
}

Transformation Transformation::inverse() {
    // I used wolfram alpha to be sure to have the correct formula
    Transformation ta;
    ta.set(
            (G*J-F*K)/(C*F*I-B*G*I-C*E*J+A*G*J+B*E*K-A*F*K),
            (C*J-B*K)/(-C*F*I+B*G*I+C*E*J-A*G*J-B*E*K+A*F*K),
            (C*F-B*G)/(C*F*I-B*G*I-C*E*J+A*G*J+B*E*K-A*F*K),
            (D*G*J-C*H*J-D*F*K+B*H*K+C*F*L-B*G*L)/(-C*F*I+B*G*I+C*E*J-A*G*J-B*E*K+A*F*K),
            (G*I-E*K)/(-C*F*I+B*G*I+C*E*J-A*G*J-B*E*K+A*F*K),
            (C*I-A*K)/(C*F*I-B*G*I-C*E*J+A*G*J+B*E*K-A*F*K),
            (C*E-A*G)/(-C*F*I+B*G*I+C*E*J-A*G*J-B*E*K+A*F*K),
            (D*G*I-C*H*I-D*E*K+A*H*K+C*E*L-A*G*L)/(C*F*I-B*G*I-C*E*J+A*G*J+B*E*K-A*F*K),
            (F*I-E*J)/(C*F*I-B*G*I-C*E*J+A*G*J+B*E*K-A*F*K),
            (B*I-A*J)/(-C*F*I+B*G*I+C*E*J-A*G*J-B*E*K+A*F*K),
            (B*E-A*F)/(C*F*I-B*G*I-C*E*J+A*G*J+B*E*K-A*F*K),
            (D*F*I-B*H*I-D*E*J+A*H*J+B*E*L-A*F*L)/(-C*F*I+B*G*I+C*E*J-A*G*J-B*E*K+A*F*K));
    return ta;
}

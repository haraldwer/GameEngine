
// https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi

double inline __declspec (naked) __fastcall Sqrt(double n)
{
	_asm fld qword ptr [esp+4]
	_asm fsqrt
	_asm ret 8
} 
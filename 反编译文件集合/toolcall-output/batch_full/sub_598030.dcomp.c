__int64 __fastcall sub_598030(int a1, unsigned int a2)
{
  double v3; // st7
  __int64 result; // rax
  __int64 v5; // [esp+8h] [ebp-18h]
  __int64 v6; // [esp+8h] [ebp-18h]
  double v7; // [esp+18h] [ebp-8h]

  v5 = a2 - a1 + 1; /*0x59803e*/
  v3 = v5; /*0x598046*/
  LODWORD(v5) = a1; /*0x59804a*/
  v7 = v5; /*0x59805a*/
  do /*0x598089*/
  {
    v6 = Randomizer::Random(&dst_); /*0x598068*/
    result = Game::F2I64(v6 * v3 * 2.328306437080797e-10 + v7); /*0x598082*/
  }
  while ( result > a2 ); /*0x598089*/
  return result; /*0x59808b*/
}

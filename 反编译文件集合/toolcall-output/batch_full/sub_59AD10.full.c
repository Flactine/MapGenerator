void __thiscall sub_59AD10(_DWORD *this)
{
  int v2; // eax
  int n2_1; // eax
  unsigned int n2; // esi
  unsigned int n2_4; // eax
  int v6; // edx
  CellClass *i; // eax
  Random *v8; // eax
  int v9; // esi
  int v10; // edi
  int v11; // ebp
  int n10_1; // esi
  int v13; // eax
  int v14; // ecx
  int v15; // eax
  _DWORD *v16; // esi
  _DWORD *v17; // edx
  int MapCoords; // [esp+10h] [ebp-50h] BYREF
  int v19; // [esp+14h] [ebp-4Ch]
  __int64 n2_2; // [esp+18h] [ebp-48h] BYREF
  double n2_3; // [esp+20h] [ebp-40h]
  int v22; // [esp+28h] [ebp-38h] BYREF
  int v23; // [esp+2Ch] [ebp-34h]
  int v24; // [esp+30h] [ebp-30h]
  int v25; // [esp+34h] [ebp-2Ch]
  _DWORD v26[4]; // [esp+38h] [ebp-28h] BYREF
  void **p_??_7?$VectorClass@V?$TRect@H@@@@6B@; // [esp+48h] [ebp-18h] BYREF
  void *Block; // [esp+4Ch] [ebp-14h]
  char v29; // [esp+55h] [ebp-Bh]
  int v30; // [esp+58h] [ebp-8h]
  int n10; // [esp+5Ch] [ebp-4h]

  this[194] = 1;
  sub_5ADA40(0, 0);
  v2 = this[20];
  p_??_7?$VectorClass@V?$TRect@H@@@@6B@ = &DynamicVectorClass<TRect<int>>::`vftable';
  n10 = 10;
  n2_1 = v2 / 2;
  v30 = 0;
  n2 = 2;
  if ( n2_1 >= 2 )
    n2 = n2_1;
  n2_2 = n2;
  n2_3 = n2;
  do
  {
    n2_2 = Randomizer::Random(&dst_);
    n2_4 = Game::F2I64(n2_2 * n2_3 * 2.328306437080797e-10 + 1.0);
  }
  while ( n2_4 > n2 );
  v26[1] = MouseClass::Instance.VisibleRect.Y;
  v26[0] = MouseClass::Instance.VisibleRect.X;
  v26[3] = MouseClass::Instance.VisibleRect.Height;
  v6 = this[20];
  v26[2] = MouseClass::Instance.VisibleRect.Width;
  sub_59A8F0(&p_??_7?$VectorClass@V?$TRect@H@@@@6B@, n2_4 + v6, v26);
  sub_578350(&MouseClass::Instance);
  for ( i = MapClass::CellIteratorNext(&MouseClass::Instance); i; i = MapClass::CellIteratorNext(&MouseClass::Instance) )
  {
    MapCoords = i->MapCoords;
    *(dword_ABED10 + 20 * MapCoords + 20 * dword_89C2DC * SHIWORD(MapCoords) + 15) = 0;
  }
  while ( v30 > 0 )
  {
    v22 = *Block;
    v23 = *(Block + 1);
    v24 = *(Block + 2);
    v25 = *(Block + 3);
    v8 = Randomizer::Random(&dst_);
    v9 = v25;
    v10 = v24;
    *&n2_3 = v8;
    v19 = 2 * v24 * v25;
    v11 = Game::F2I64((v8 * 2.328306437080797e-10 * 0.05 + 0.45) * v19);
    LODWORD(n2_2) = v22 + v10 / 2 + v9 / 2 + v23 + 1;
    HIDWORD(n2_2) = v23 + MouseClass::Instance.MapRect.Width + v9 / 2 - v10 / 2 - v22;
    n10_1 = 0;
    do
    {
      if ( n10_1 >= 10 )
        break;
      LOWORD(MapCoords) = n2_2;
      HIWORD(MapCoords) = WORD2(n2_2);
      v13 = sub_59BBC0(v11, &v22, &n2_2, 1, &MapCoords, 0.25, 0);
      if ( !v13 )
        ++this[194];
      ++n10_1;
    }
    while ( !v13 );
    if ( v30 <= 0 )
      break;
    v14 = 0;
    if ( --v30 <= 0 )
      break;
    v15 = 0;
    do
    {
      v16 = Block + v15 + 16;
      v17 = Block + v15;
      ++v14;
      v15 += 16;
      *v17 = *v16;
      v17[1] = v16[1];
      v17[2] = v16[2];
      v17[3] = v16[3];
    }
    while ( v14 < v30 );
  }
  p_??_7?$VectorClass@V?$TRect@H@@@@6B@ = &VectorClass<TRect<int>>::`vftable';
  if ( Block )
  {
    if ( v29 )
      operator delete(Block);
  }
}

void __stdcall sub_59A8F0(void ***p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@, signed int a2, int *a3)
{
  double number; // st7
  int v4; // eax
  int v5; // ebx
  int v6; // esi
  int *v7; // ebp
  int v8; // esi
  int v9; // edi
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // edi
  unsigned int v14; // esi
  signed int v15; // eax
  int v16; // edi
  int v17; // ecx
  void **v18; // eax
  void **v19; // ecx
  void **v20; // eax
  void **v21; // edx
  bool v22; // zf
  int v23; // [esp+18h] [ebp-74h]
  int v24; // [esp+1Ch] [ebp-70h]
  __int64 v25; // [esp+20h] [ebp-6Ch]
  int v26; // [esp+28h] [ebp-64h]
  int v27; // [esp+2Ch] [ebp-60h]
  int v28; // [esp+30h] [ebp-5Ch]
  int v29; // [esp+38h] [ebp-54h]
  int v30; // [esp+3Ch] [ebp-50h]
  int v31; // [esp+40h] [ebp-4Ch]
  int j; // [esp+40h] [ebp-4Ch]
  int v33; // [esp+44h] [ebp-48h]
  int v34; // [esp+48h] [ebp-44h]
  __int64 v35; // [esp+4Ch] [ebp-40h]
  double v36; // [esp+54h] [ebp-38h]
  CDTimerClass_vtbl *p_??_7?$DynamicVectorClass@H@@6B@_1; // [esp+5Ch] [ebp-30h] BYREF
  void *Block; // [esp+60h] [ebp-2Ch]
  int v39; // [esp+64h] [ebp-28h]
  int v40; // [esp+68h] [ebp-24h]
  int i; // [esp+6Ch] [ebp-20h]
  int n10_1; // [esp+70h] [ebp-1Ch]
  CDTimerClass_vtbl *p_??_7?$DynamicVectorClass@H@@6B@; // [esp+74h] [ebp-18h] BYREF
  void *v44; // [esp+78h] [ebp-14h]
  int v45; // [esp+7Ch] [ebp-10h]
  char v46; // [esp+81h] [ebp-Bh]
  int v47; // [esp+84h] [ebp-8h]
  int n10; // [esp+88h] [ebp-4h]

  number = YRMath::sqrt(a2);
  v4 = Game::F2I64(number);
  v31 = v4;
  if ( v4 * v4 == a2 )
  {
    v5 = v4;
    v26 = v4;
  }
  else
  {
    v26 = v4 + 1;
    v5 = v4 + 1;
  }
  if ( v4 * v5 < a2 )
  {
    v23 = v5;
    v6 = v5;
  }
  else
  {
    v6 = v4;
    v23 = v4;
  }
  v7 = a3;
  v24 = a3[2] / v5;
  v25 = (a3[3] / v5);
  v29 = 0;
  v30 = 0;
  v27 = 0;
  if ( Randomizer::Random(&dst_) * 2.328306437080797e-10 >= 0.5 )
  {
    HIDWORD(v25) = v24;
    LODWORD(v25) = a3[3] / v6;
    v30 = v25;
  }
  else
  {
    v27 = v25;
    v24 = a3[2] / v6;
    v29 = v24;
  }
  v8 = v5 * v6 - a2;
  v9 = 0;
  v34 = a3[1];
  v33 = *a3;
  sub_477BE0(&p_??_7?$DynamicVectorClass@H@@6B@, 0, 0);
  p_??_7?$DynamicVectorClass@H@@6B@ = &DynamicVectorClass<int>::`vftable';
  n10 = 10;
  v47 = 0;
  sub_477BE0(&p_??_7?$DynamicVectorClass@H@@6B@_1, 0, 0);
  v10 = 0;
  p_??_7?$DynamicVectorClass@H@@6B@_1 = &DynamicVectorClass<int>::`vftable';
  n10_1 = 10;
  i = 0;
  if ( v23 > 0 )
  {
    do
    {
      if ( v47 < v45
        || (v46 || !v45)
        && n10 > 0
        && (p_??_7?$DynamicVectorClass@H@@6B@->sub_477C70)(&p_??_7?$DynamicVectorClass@H@@6B@, n10 + v45, 0) )
      {
        v11 = v47++;
        *(v44 + v11) = v5;
      }
      if ( i < v39
        || (BYTE1(v40) || !v39)
        && n10_1 > 0
        && (p_??_7?$DynamicVectorClass@H@@6B@_1->sub_477C70)(&p_??_7?$DynamicVectorClass@H@@6B@_1, n10_1 + v39, 0) )
      {
        v12 = i++;
        *(Block + v12) = v9;
      }
      ++v9;
    }
    while ( v9 < v23 );
    v10 = i;
  }
  if ( v8 > 0 )
  {
    v13 = v8;
    do
    {
      v14 = v10 - 1;
      v36 = v10;
      do
      {
        v35 = Randomizer::Random(&dst_);
        v15 = Game::F2I64(v35 * v36 * 2.328306437080797e-10);
      }
      while ( v15 > v14 );
      *(v44 + *(Block + v15)) = v31;
      v10 = i;
      if ( v15 < i )
      {
        v10 = i - 1;
        for ( i = v10; v15 < i; v10 = i )
        {
          ++v15;
          *(Block + v15 - 1) = *(Block + v15);
        }
      }
      --v13;
    }
    while ( v13 );
  }
  v16 = 0;
  for ( j = 0; v16 < v23; j = v16 )
  {
    v17 = *(v44 + v16);
    if ( v17 < v5 )
    {
      if ( SHIDWORD(v25) <= 0 )
        v34 += v25 / 2;
      else
        v33 += v24 / 2;
    }
    if ( v17 > 0 )
    {
      v28 = *(v44 + v16);
      do
      {
        v18 = p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@[2];
        if ( p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@[4] < v18
          || (*(p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@ + 13) || !v18)
          && (v19 = p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@[5], v19 > 0)
          && ((*p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@)[2])(
               p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@,
               v19 + v18,
               0) )
        {
          v20 = p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@[4];
          p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@[4] = (v20 + 1);
          v21 = &p_p_??_7?$DynamicVectorClass@V?$TRect@H@@@@6B@[1][4 * v20];
          *v21 = (v33 + 2);
          v21[1] = (v34 + 2);
          v21[2] = (v24 - 4);
          v21[3] = (v25 - 4);
        }
        v33 += HIDWORD(v25);
        v22 = v28 == 1;
        v34 += v27;
        --v28;
      }
      while ( !v22 );
      v5 = v26;
      v7 = a3;
      v16 = j;
    }
    v33 += v29;
    v34 += v30;
    if ( SHIDWORD(v25) <= 0 )
      v34 = v7[1];
    else
      v33 = *v7;
    ++v16;
  }
  p_??_7?$DynamicVectorClass@H@@6B@_1 = &CDTimerClass_vtbl_;
  if ( Block && BYTE1(v40) )
  {
    operator delete(Block);
    Block = 0;
  }
  p_??_7?$DynamicVectorClass@H@@6B@ = &CDTimerClass_vtbl_;
  BYTE1(v40) = 0;
  v39 = 0;
  if ( v44 )
  {
    if ( v46 )
      operator delete(v44);
  }
}

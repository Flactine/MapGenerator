int __thiscall sub_59B200(int *this)
{
  CellClass *i; // eax
  int v3; // esi
  double v4; // st7
  int n400; // eax
  int v6; // edi
  int n50000; // ebp
  int v8; // ebx
  __int16 *v9; // esi
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // eax
  __int64 v14; // rax
  int n50000_1; // eax
  bool v16; // zf
  int result; // eax
  int v18; // [esp+10h] [ebp-B8h]
  int n2; // [esp+10h] [ebp-B8h]
  int p_n2_2; // [esp+14h] [ebp-B4h]
  double v21; // [esp+18h] [ebp-B0h]
  int v22; // [esp+20h] [ebp-A8h]
  int n100; // [esp+24h] [ebp-A4h]
  int v24; // [esp+28h] [ebp-A0h]
  int *v25; // [esp+2Ch] [ebp-9Ch]
  int v26; // [esp+30h] [ebp-98h] BYREF
  int v27; // [esp+34h] [ebp-94h]
  int v28; // [esp+38h] [ebp-90h]
  int v29; // [esp+3Ch] [ebp-8Ch]
  double v30; // [esp+40h] [ebp-88h]
  int p_MapCoords; // [esp+4Ch] [ebp-7Ch] BYREF
  int p_n2_1; // [esp+50h] [ebp-78h]
  int v33; // [esp+54h] [ebp-74h]
  int v34; // [esp+58h] [ebp-70h]
  int *this_1; // [esp+5Ch] [ebp-6Ch]
  int p_n2; // [esp+60h] [ebp-68h] BYREF
  int v37; // [esp+64h] [ebp-64h]
  double v38; // [esp+68h] [ebp-60h]
  double v39; // [esp+70h] [ebp-58h]
  _DWORD v40[2]; // [esp+78h] [ebp-50h] BYREF
  int Width; // [esp+80h] [ebp-48h]
  int Height; // [esp+84h] [ebp-44h]
  int X; // [esp+88h] [ebp-40h]
  int Y; // [esp+8Ch] [ebp-3Ch]
  int Width_1; // [esp+90h] [ebp-38h]
  int Height_1; // [esp+94h] [ebp-34h]
  int v47; // [esp+98h] [ebp-30h]
  int n400_1; // [esp+9Ch] [ebp-2Ch]
  double v49; // [esp+A0h] [ebp-28h]
  double v50; // [esp+A8h] [ebp-20h]
  int v51; // [esp+B4h] [ebp-14h]
  double v52; // [esp+B8h] [ebp-10h]
  double v53; // [esp+C0h] [ebp-8h]

  this_1 = this; /*0x59b212*/
  this[194] = 1; /*0x59b216*/
  v18 = sub_42B1F0(); /*0x59b228*/
  n100 = 0; /*0x59b22e*/
  v38 = (1.0 - this[19] * 0.01) * (0.2 - 0.15) + 0.15; /*0x59b252*/
  v50 = v18; /*0x59b25a*/
  n400_1 = Game::F2I64(v50 * 0.06 * v38); /*0x59b275*/
  sub_578350(&MouseClass::Instance); /*0x59b27c*/
  for ( i = MapClass::CellIteratorNext(&MouseClass::Instance); i; i = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x59b28d*/
    *(dword_ABED10 + 20 * *&i->MapCoords + 20 * dword_89C2DC * HIWORD(*&i->MapCoords) + 15) = 0; /*0x59b2b7*/
  *&v30 = Randomizer::Random(&dst_); /*0x59b2ce*/
  v40[0] = MouseClass::Instance.VisibleRect.X; /*0x59b2fe*/
  v40[1] = MouseClass::Instance.VisibleRect.Y; /*0x59b30d*/
  if ( *&v30 * 2.328306437080797e-10 >= 0.5 ) /*0x59b2f7*/
  {
    Width = MouseClass::Instance.VisibleRect.Width; /*0x59b35c*/
    Height = MouseClass::Instance.VisibleRect.Height / 2 - 1; /*0x59b36a*/
    X = MouseClass::Instance.VisibleRect.X; /*0x59b371*/
    Y = MouseClass::Instance.VisibleRect.Height / 2 + MouseClass::Instance.VisibleRect.Y + 1; /*0x59b378*/
    Width_1 = MouseClass::Instance.VisibleRect.Width; /*0x59b37f*/
    Height_1 = Height; /*0x59b386*/
  }
  else
  {
    Height = MouseClass::Instance.VisibleRect.Height; /*0x59b311*/
    Width = MouseClass::Instance.VisibleRect.Width / 2 - 1; /*0x59b31f*/
    X = MouseClass::Instance.VisibleRect.Width / 2 + MouseClass::Instance.VisibleRect.X + 1; /*0x59b326*/
    Y = MouseClass::Instance.VisibleRect.Y; /*0x59b32d*/
    Width_1 = Width; /*0x59b334*/
    Height_1 = MouseClass::Instance.VisibleRect.Height; /*0x59b33b*/
  }
  n2 = 2; /*0x59b391*/
  v25 = v40; /*0x59b399*/
  do /*0x59b6c1*/
  {
    v22 = 0; /*0x59b3a5*/
    v39 = 0.0; /*0x59b3a9*/
    v26 = *v25; /*0x59b3bb*/
    v27 = v25[1]; /*0x59b3c2*/
    v28 = v25[2]; /*0x59b3cb*/
    v29 = v25[3]; /*0x59b3d5*/
    v3 = v27 + MouseClass::Instance.MapRect.Width + v29 / 2 - v28 / 2 - v26; /*0x59b3fd*/
    p_n2_1 = v26 + v29 / 2 + v28 / 2 + v27 + 1; /*0x59b3ff*/
    v33 = v3; /*0x59b403*/
    p_n2 = p_n2_1; /*0x59b407*/
    v37 = v3; /*0x59b40b*/
    if ( v29 <= v28 ) /*0x59b40f*/
    {
      v4 = v28; /*0x59b445*/
      v30 = 1.0; /*0x59b44d*/
      v21 = v29; /*0x59b45d*/
      v49 = v4 / v21 * 1.2; /*0x59b46d*/
    }
    else
    {
      v49 = 1.0; /*0x59b415*/
      v21 = v29; /*0x59b42b*/
      v4 = v28; /*0x59b42f*/
      v30 = v21 / v4 * 1.2; /*0x59b43f*/
    }
    v53 = 1.0 / (v4 * 0.5 * (v4 * 0.5)); /*0x59b484*/
    v52 = 1.0 / (v21 * 0.5 * (v21 * 0.5)); /*0x59b4a1*/
    if ( v38 > 0.0 ) /*0x59b4b9*/
    {
      do /*0x59b6a7*/
      {
        if ( n100 >= 100 ) /*0x59b4c4*/
          break; /*0x59b4c4*/
        n400 = Game::F2I64((v38 - v39) * v50); /*0x59b4d9*/
        if ( n400 >= n400_1 ) /*0x59b4e7*/
          n400 = n400_1; /*0x59b4e9*/
        LOWORD(p_MapCoords) = p_n2_1; /*0x59b4fd*/
        HIWORD(p_MapCoords) = v3; /*0x59b515*/
        v22 += sub_59BBC0(this_1, n400, &v26, &p_n2, 1, &p_MapCoords, 0.75, 1); /*0x59b52d*/
        p_n2_2 = 0; /*0x59b540*/
        ++n100; /*0x59b55a*/
        v6 = 2 * v26 - MouseClass::Instance.MapRect.Width + 1; /*0x59b562*/
        n50000 = 50000; /*0x59b563*/
        v47 = v6 + 2 * v28 + 2; /*0x59b572*/
        v8 = MouseClass::Instance.MapRect.Width + 2 * v27 + 1; /*0x59b57d*/
        v51 = v8 + 2 * v29 + 2; /*0x59b585*/
        v39 = v22 / v50; /*0x59b58c*/
        if ( dword_89C2DC * dword_89C2DC > 0 ) /*0x59b590*/
        {
          v24 = 0; /*0x59b596*/
          v34 = dword_89C2DC * dword_89C2DC; /*0x59b59e*/
          do /*0x59b67e*/
          {
            v9 = (dword_ABED10 + v24); /*0x59b5ab*/
            v10 = *(dword_ABED10 + v24 + 2); /*0x59b5ae*/
            v11 = *(dword_ABED10 + v24); /*0x59b5b3*/
            v12 = v11 + v10; /*0x59b5b6*/
            v13 = v11 - v10; /*0x59b5b9*/
            if ( v12 >= v8 /*0x59b618*/
              && v12 <= v51
              && v13 >= v6
              && v13 <= v47
              && !*(v9 + 15)
              && sub_59BAB0((dword_ABED10 + v24), &v26, 1, v53, v52) )
            {
              v14 = v9[1] - v33; /*0x59b629*/
              n50000_1 = Game::F2I64(((HIDWORD(v14) ^ v14) - HIDWORD(v14)) * v49 + abs32(*v9 - p_n2_1) * v30); /*0x59b659*/
              if ( n50000_1 < n50000 ) /*0x59b660*/
              {
                n50000 = n50000_1; /*0x59b664*/
                p_n2_2 = *v9; /*0x59b666*/
              }
            }
            v16 = v34 == 1; /*0x59b675*/
            v24 += 80; /*0x59b676*/
            --v34; /*0x59b67a*/
          }
          while ( !v16 ); /*0x59b67e*/
          LOWORD(v3) = v33; /*0x59b684*/
        }
        p_n2 = p_n2_2; /*0x59b69a*/
        v37 = SHIWORD(p_n2_2); /*0x59b69e*/
      }
      while ( v39 < v38 ); /*0x59b6a7*/
    }
    result = n2 - 1; /*0x59b6b8*/
    v16 = n2 == 1; /*0x59b6b8*/
    v25 += 4; /*0x59b6b9*/
    --n2; /*0x59b6bd*/
  }
  while ( !v16 ); /*0x59b6c1*/
  return result; /*0x59b6c7*/
}
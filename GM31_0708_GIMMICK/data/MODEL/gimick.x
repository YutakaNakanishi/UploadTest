xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 86;
 0.00000;1.46838;-20.00000;,
 5.89510;1.46838;-19.11146;,
 5.89510;-1.46838;-19.11146;,
 0.00000;-1.46838;-20.00000;,
 11.26640;1.46838;-16.52478;,
 11.26640;-1.46838;-16.52478;,
 15.63663;1.46838;-12.46980;,
 15.63663;-1.46838;-12.46980;,
 18.61748;1.46838;-7.30682;,
 18.61748;-1.46838;-7.30682;,
 19.94408;1.46838;-1.49460;,
 19.94408;-1.46838;-1.49460;,
 19.49856;1.46838;4.45042;,
 19.49856;-1.46838;4.45042;,
 17.32051;1.46838;10.00000;,
 17.32051;-1.46838;10.00000;,
 13.60345;1.46838;14.66104;,
 13.60345;-1.46838;14.66104;,
 8.67767;1.46838;18.01938;,
 8.67767;-1.46838;18.01938;,
 2.98084;1.46838;19.77662;,
 2.98084;-1.46838;19.77662;,
 -2.98085;1.46838;19.77662;,
 -2.98085;-1.46838;19.77662;,
 -8.67768;1.46838;18.01938;,
 -8.67768;-1.46838;18.01938;,
 -13.60346;1.46838;14.66103;,
 -13.60346;-1.46838;14.66103;,
 -17.32051;1.46838;10.00000;,
 -17.32051;-1.46838;10.00000;,
 -19.49856;1.46838;4.45042;,
 -19.49856;-1.46838;4.45042;,
 -19.94408;1.46838;-1.49460;,
 -19.94408;-1.46838;-1.49460;,
 -18.61748;1.46838;-7.30681;,
 -18.61748;-1.46838;-7.30681;,
 -15.63664;1.46838;-12.46979;,
 -15.63664;-1.46838;-12.46979;,
 -11.26642;1.46838;-16.52477;,
 -11.26642;-1.46838;-16.52477;,
 -5.89512;1.46838;-19.11145;,
 -5.89512;-1.46838;-19.11145;,
 0.00000;1.46838;-20.00000;,
 0.00000;-1.46838;-20.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;1.46838;0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;,
 0.00000;-1.46838;-0.00000;;
 
 63;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 3;44,1,0;,
 3;45,4,1;,
 3;46,6,4;,
 3;47,8,6;,
 3;48,10,8;,
 3;49,12,10;,
 3;50,14,12;,
 3;51,16,14;,
 3;52,18,16;,
 3;53,20,18;,
 3;54,22,20;,
 3;55,24,22;,
 3;56,26,24;,
 3;57,28,26;,
 3;58,30,28;,
 3;59,32,30;,
 3;60,34,32;,
 3;61,36,34;,
 3;62,38,36;,
 3;63,40,38;,
 3;64,42,40;,
 3;65,3,2;,
 3;66,2,5;,
 3;67,5,7;,
 3;68,7,9;,
 3;69,9,11;,
 3;70,11,13;,
 3;71,13,15;,
 3;72,15,17;,
 3;73,17,19;,
 3;74,19,21;,
 3;75,21,23;,
 3;76,23,25;,
 3;77,25,27;,
 3;78,27,29;,
 3;79,29,31;,
 3;80,31,33;,
 3;81,33,35;,
 3;82,35,37;,
 3;83,37,39;,
 3;84,39,41;,
 3;85,41,43;;
 
 MeshMaterialList {
  1;
  63;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  23;
  0.000000;1.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.294755;0.000000;-0.955573;,
  0.563320;0.000000;-0.826239;,
  0.781831;0.000000;-0.623490;,
  0.930874;0.000000;-0.365341;,
  0.997204;0.000000;-0.074730;,
  0.974928;0.000000;0.222521;,
  0.866025;0.000000;0.500000;,
  0.680173;0.000000;0.733052;,
  0.433884;0.000000;0.900969;,
  0.149042;0.000000;0.988831;,
  -0.149042;0.000000;0.988831;,
  -0.433884;0.000000;0.900969;,
  -0.680173;0.000000;0.733052;,
  -0.866025;0.000000;0.500000;,
  -0.974928;0.000000;0.222521;,
  -0.997204;0.000000;-0.074730;,
  -0.930874;0.000000;-0.365341;,
  -0.781832;0.000000;-0.623489;,
  -0.563321;0.000000;-0.826238;,
  -0.294756;0.000000;-0.955572;,
  0.000000;-1.000000;-0.000000;;
  63;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,1,1,21;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;;
 }
 MeshTextureCoords {
  86;
  0.000000;0.000000;,
  0.047619;0.000000;,
  0.047619;1.000000;,
  0.000000;1.000000;,
  0.095238;0.000000;,
  0.095238;1.000000;,
  0.142857;0.000000;,
  0.142857;1.000000;,
  0.190476;0.000000;,
  0.190476;1.000000;,
  0.238095;0.000000;,
  0.238095;1.000000;,
  0.285714;0.000000;,
  0.285714;1.000000;,
  0.333333;0.000000;,
  0.333333;1.000000;,
  0.380952;0.000000;,
  0.380952;1.000000;,
  0.428571;0.000000;,
  0.428571;1.000000;,
  0.476190;0.000000;,
  0.476190;1.000000;,
  0.523810;0.000000;,
  0.523810;1.000000;,
  0.571429;0.000000;,
  0.571429;1.000000;,
  0.619048;0.000000;,
  0.619048;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.714286;0.000000;,
  0.714286;1.000000;,
  0.761905;0.000000;,
  0.761905;1.000000;,
  0.809524;0.000000;,
  0.809524;1.000000;,
  0.857143;0.000000;,
  0.857143;1.000000;,
  0.904762;0.000000;,
  0.904762;1.000000;,
  0.952381;0.000000;,
  0.952381;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.023810;0.000000;,
  0.071429;0.000000;,
  0.119048;0.000000;,
  0.166667;0.000000;,
  0.214286;0.000000;,
  0.261905;0.000000;,
  0.309524;0.000000;,
  0.357143;0.000000;,
  0.404762;0.000000;,
  0.452381;0.000000;,
  0.500000;0.000000;,
  0.547619;0.000000;,
  0.595238;0.000000;,
  0.642857;0.000000;,
  0.690476;0.000000;,
  0.738095;0.000000;,
  0.785714;0.000000;,
  0.833333;0.000000;,
  0.880952;0.000000;,
  0.928571;0.000000;,
  0.976191;0.000000;,
  0.023810;1.000000;,
  0.071429;1.000000;,
  0.119048;1.000000;,
  0.166667;1.000000;,
  0.214286;1.000000;,
  0.261905;1.000000;,
  0.309524;1.000000;,
  0.357143;1.000000;,
  0.404762;1.000000;,
  0.452381;1.000000;,
  0.500000;1.000000;,
  0.547619;1.000000;,
  0.595238;1.000000;,
  0.642857;1.000000;,
  0.690476;1.000000;,
  0.738095;1.000000;,
  0.785714;1.000000;,
  0.833333;1.000000;,
  0.880952;1.000000;,
  0.928571;1.000000;,
  0.976191;1.000000;;
 }
}
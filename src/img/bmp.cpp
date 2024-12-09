#include <fstream>
#include <iostream>
#include <vector>

#pragma pack(push, 1)
struct BMPFileHeader {
  uint16_t fileType;    // ファイルタイプ（必ず 'BM'）
  uint32_t fileSize;    // ファイルサイズ
  uint16_t reserved1;   // 予約領域（0）
  uint16_t reserved2;   // 予約領域（0）
  uint32_t offsetData;  // ピクセルデータのオフセット
};

struct BMPInfoHeader {
  uint32_t size;             // ヘッダーのサイズ
  int32_t width;             // 画像の幅
  int32_t height;            // 画像の高さ
  uint16_t planes;           // プレーン数（必ず1）
  uint16_t bitCount;         // ビット深度（1, 4, 8, 16, 24, 32）
  uint32_t compression;      // 圧縮方式（0 = 無圧縮）
  uint32_t sizeImage;        // 画像データのサイズ
  int32_t xPixelsPerMeter;   // 水平解像度
  int32_t yPixelsPerMeter;   // 垂直解像度
  uint32_t colorsUsed;       // 使用する色数
  uint32_t colorsImportant;  // 重要な色数
};
#pragma pack(pop)

int main() {
  std::ifstream file("../../data/lena_gray.bmp", std::ios::binary);
  if (!file) {
    std::cerr << "ファイルを開けませんでした。" << std::endl;
    return 1;
  }

  BMPFileHeader fileHeader;
  BMPInfoHeader infoHeader;

  // ファイルヘッダーの読み取り
  file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
  if (fileHeader.fileType != 0x4D42) {  // 'BM' であることを確認
    std::cerr << "これはBMPファイルではありません。" << std::endl;
    return 1;
  }

  // 情報ヘッダーの読み取り
  file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

  // ピクセルデータの読み取り
  file.seekg(fileHeader.offsetData, std::ios::beg);
  std::vector<uint8_t> pixelData(infoHeader.sizeImage);
  file.read(reinterpret_cast<char*>(pixelData.data()), pixelData.size());

  // 画像データの処理（ここでは単に表示するだけ）
  std::cout << "画像の幅: " << infoHeader.width << std::endl;
  std::cout << "画像の高さ: " << infoHeader.height << std::endl;
  std::cout << "ビット深度: " << infoHeader.bitCount << std::endl;

  file.close();
  return 0;
}

## 文件格式的定义


unsigned int Reader::ReadPhysicalRecord(Slice* result) 

|---4byte---|--2byte---|1byte |(datalen-7)|
|-----CRC---|--datalen-| type |data_part  |

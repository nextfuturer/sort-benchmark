# **BÁO CÁO ĐỒ ÁN SORT BENCHMARK**

## **1\. THÔNG TIN SINH VIÊN**

* **Tên môn học:** Cấu trúc Dữ liệu và Giải thuật  
* **Thời gian học:** Học kỳ 2, Năm học 2025-2026  
* **Họ tên sinh viên:** Lê Thiên Tấn, Nguyễn Thiên Võ, Phạm Minh Thiện  
* **MSSV:** 25120434, 25120473, 25120441

## **2\. THUẬT TOÁN TỐT NHẤT Ở LẦN CHẠY ĐẦU TIÊN (BENCHMARK 1\)**

Ở lần chạy đầu tiên, ưu tiên hàng đầu của chúng em là hoàn thành sớm và đảm bảo tính đúng đắn của chương trình trên các bộ test cơ bản, đồng thời kiểm soát chặt chẽ giới hạn bộ nhớ (Memory Limit):

* **Bài A (Integer Sort):** Chúng em sử dụng hàm std::sort kết hợp với std::greater\<int\>() để sắp xếp nếu cần.  
  * *Lý do:* Hàm std::sort của C++ cài đặt thuật toán IntroSort (kết hợp QuickSort, HeapSort và InsertionSort). Nó đảm bảo độ phức tạp thời gian luôn ở mức ![][image1] và độ phức tạp không gian chỉ là ![][image2], an toàn tuyệt đối trước lỗi tràn bộ nhớ (MLE) cho dù mảng lên tới ![][image3] phần tử.  
* **Bài B (Lexicographic Sort):** Tương tự Bài A, chúng em sử dụng std::sort kết hợp Fast I/O (cin.tie(NULL)).  
  * *Lý do:* Việc triển khai một cấu trúc dữ liệu phức tạp như Trie tĩnh mảng 2D cho ![][image3] chuỗi (mỗi chuỗi tối đa 100 ký tự) sẽ tiêu tốn khoảng 1GB RAM, dẫn đến việc bị hệ thống chấm rớt ngay lập tức. Hàm sort tích hợp sẵn là phương pháp an toàn nhất.  
* **Bài C (Length-aware Lexicographic Sort):** Chúng em sử dụng std::sort với một hàm so sánh (Comparator) tự định nghĩa.  
  * *Lý do:* Hàm cmp được viết đơn giản: kiểm tra chiều dài bằng hàm .length() trước, nếu bằng nhau thì dùng toán tử \< để so sánh chuỗi. Cách tiếp cận này giúp giải quyết nhanh yêu cầu của đề bài.

## **3\. CÁCH THỨC SINH TEST CASE (VÒNG HACKING)**

Sau khi quan sát các bài nộp Lần 1, chúng em nhận thấy đa số các bạn đều dùng std::sort hoặc QuickSort tự viết. Chương trình test\_gen.cpp được chúng em thiết kế đặc biệt để khai thác triệt để các lỗ hổng của những thuật toán này:

### **Bài A (int): Mục tiêu bẫy QuickSort và Radix Sort cơ bản**

1. **Test 1 (Mảng giảm dần):** Ép QuickSort (nếu cài đặt chọn chốt ở đầu/cuối mảng) rơi thẳng vào trường hợp xấu nhất ![][image4], gây Time Limit Exceeded (TLE).  
2. **Test 2 (Toàn số trùng lặp):** Bẫy các thuật toán phân hoạch không sử dụng kỹ thuật 3-way partitioning. Khi mảng toàn số giống nhau, chúng không thể chia đôi mảng đều đặn, dẫn đến ![][image4].  
3. **Test 3 (Âm/Dương xen kẽ sát mức giới hạn):** Sinh các số gần INT\_MIN và INT\_MAX. Nhắm vào các bạn dùng Radix Sort nhưng xử lý bit dấu sai hoặc ép kiểu bị tràn bộ đệm.  
4. **Test 4 (Mảng V-Shape \- Nửa giảm, nửa tăng):** Thiết kế dữ liệu phá vỡ khả năng phán đoán của Branch Predictor trong CPU, làm chậm quá trình so sánh rẽ nhánh.  
5. **Test 5 (Thuần ngẫu nhiên):** Ép băng thông I/O lên mức cao nhất để kiểm tra khả năng đọc/ghi của chương trình.

### **Bài B (strlexi): Mục tiêu làm quá tải phép so sánh chuỗi của std::sort**

1. **Test 1 (Ngẫu nhiên):** Đánh giá tốc độ xử lý cơ bản trên dải ký tự từ 'a' đến 'z'.  
2. **Test 2 (Tiền tố chung siêu dài):** Đặt 90 ký tự đầu của toàn bộ ![][image3] chuỗi giống hệt nhau. Khi dùng operator\< để sort, máy tính phải so sánh lại 90 ký tự vô ích này hàng trăm triệu lần, trực tiếp làm sập (TLE) thuật toán std::sort.  
3. **Test 3 (Toàn chuỗi trùng lặp):** Khai thác lỗi cấp phát bộ nhớ dư thừa hoặc lặp vô tận ở các thuật toán đệ quy chưa hoàn thiện.  
4. **Test 4 (Sắp xếp ngược bảng chữ cái):** Đẩy số lượng phép hoán vị (Swap) trong bộ nhớ lên mức kịch trần.  
5. **Test 5 (Giới hạn ký tự chỉ 'a' và 'b'):** Làm tăng xác suất trùng lặp các đoạn nhỏ trong chuỗi, tạo ra hiệu ứng nghẽn cổ chai tương tự Test 2\.

### **Bài C (strlenlexi): Mục tiêu bẫy hàm tính chiều dài length()**

1. **Test 1 (Ngẫu nhiên):** Đảm bảo thuật toán tuân thủ đúng yêu cầu sắp xếp theo độ dài trước.  
2. **Test 2 (Cùng độ dài tối đa 100, xếp ngược):** Loại bỏ lợi thế phân loại theo chiều dài, ép hệ thống phải so sánh chuỗi nguyên vẹn trên mảng lớn.  
3. **Test 3 (Tiền tố giống nhau, chiều dài ngẫu nhiên xen kẽ):** Buộc hàm cmp của đối thủ phải liên tục nhảy qua lại giữa việc đếm ký tự và so sánh mã ASCII, làm mất hiệu suất của Cache CPU.  
4. **Test 4 (Sắp xếp ngược chiều dài):** Nhắm vào các thuật toán Bucket Sort cài đặt sai thứ tự duyệt index các xô.  
5. **Test 5 (Toàn chuỗi trùng lặp):** Đảm bảo tính ổn định của việc in ra đủ số lượng bản sao.

## **4\. THUẬT TOÁN TỐT NHẤT Ở LẦN THỨ HAI (BENCHMARK 2\)**

Nhận thức được sự yếu kém của thuật toán Lần 1 trước các "bẫy" dữ liệu do chính mình và các bạn thiết kế, chúng em đã kiến trúc lại toàn bộ hệ thống ở Lần 2 nhằm đạt độ phức tạp tiệm cận tuyến tính và miễn nhiễm với mọi "Test bẩn" (Dirty Data):

* **Bài A (int):** Thay thế bằng **LSD Radix Sort (Cơ số 256\) tích hợp Ping-Pong Buffer**.  
  * *Tối ưu:* Thuật toán sắp xếp 4 lần (mỗi lần 8-bit). Kỹ thuật Ping-Pong Buffer (luân chuyển dữ liệu tĩnh giữa hai mảng qua tham chiếu) giúp loại bỏ hoàn toàn các lệnh copy mảng a \= ketqua tốn kém. Việc xử lý số âm được thực hiện bằng phép đảo bit dấu XOR 0x80000000 (nhanh hơn nhiều so với phép chia hệ thập phân).  
* **Bài B (strlexi):** Thay thế bằng **MSD Radix Sort (In-place ảo)**.  
  * *Tối ưu:* Để giải quyết bẫy "Tiền tố dài" mà không bị tràn bộ nhớ (MLE) như khi dùng Trie tĩnh, MSD Radix Sort mô phỏng lại logic rẽ nhánh của Trie bằng cách chia xô (Bucketing) đệ quy ngay trên mảng. Nó phân loại chuỗi theo từng cột ký tự, triệt tiêu hoàn toàn việc so sánh lại các đoạn tiền tố đã giống nhau.  
* **Bài C (strlenlexi):** Áp dụng kiến trúc **Hybrid Sort (std::sort theo độ dài \+ MSD Radix Sort chuẩn ASCII)**.  
  * *Thay đổi chiến thuật:* Ban đầu chúng em định dùng Trie tĩnh, nhưng nhận ra cấu trúc Trie rất mỏng manh trước các "Test bẩn" (Ví dụ: chứa ký tự lạ ngoài a-z làm âm chỉ số mảng, hoặc nhồi khối lượng node khổng lồ gây tràn RAM). Do đó, chúng em chuyển sang chiến thuật an toàn tuyệt đối.  
  * *Tối ưu:* 1\. Đầu tiên, dùng std::sort với hàm Comparator **CHỈ** so sánh chiều dài. Phép so sánh này tốn ![][image5], chạy cực nhanh và không bao giờ bị TLE.  
    2\. Sau đó, chúng em gom các chuỗi có **cùng chiều dài** thành từng cụm, và đưa cụm đó vào hàm MSD Radix Sort.  
    3\. Hàm Radix Sort được nâng cấp dùng mảng đếm 258 ô (unsigned char), qua đó cover toàn bộ 256 ký tự của bảng mã ASCII, biến code trở nên "bất tử" trước mọi nỗ lực Hacking bằng ký tự lạ, đồng thời không tiêu tốn RAM.  
  * *Tối ưu vi mô cực hạn:* Trong quá trình test thực tế hệ thống Hybrid Sort, chúng em phát hiện mảng std::string khi gán bằng dấu \= trong các vòng đệ quy sẽ gây ra hiện tượng Deep Copy (sao chép sâu), khiến chương trình phải xin cấp phát RAM liên tục và bị TLE (\>10s). Để khắc phục triệt để, chúng em đã áp dụng ngữ nghĩa di chuyển (**Move Semantics**) với hàm std::move() của C++11. Việc này chuyển hóa hoàn toàn Deep Copy thành Pointer Swap (hoán vị con trỏ), giúp triệt tiêu hàng triệu lệnh cấp phát bộ nhớ thừa, ép thời gian chạy từ hơn 10 giây xuống chỉ còn vài trăm mili-giây (![][image5] cho mỗi phép gán).

[image1]: <data:image/png;base64,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>

[image2]: <data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFEAAAAaCAYAAADPELCZAAAFBUlEQVR4Xu1Yb2iWVRR/Xl6LouyfrbV/733ebTg2gohhMbAvI9KFhKTQyL5rsE9CRkQfRIIoBBkrRVrRh7kPBhKpCxE1BREFLUgCSaiQhcJ8QZiooev32z13np33ed49072a8f7g8Lz3nHPvPefce889942iGmr4X6K7u/uh5ubmZyz/AUGuUCg8jW/eCu4KcRw/5ZxriDIM3Nra+iR094DWWNkDghxsHwCN0BcrnDcw0BegK6BxrM5f+N4EDba3tz9hdQkJ4BiC/iGaOXw3SL8L7Gv1qwlZ+C85v9jwdVNT0xKt09LS8ir4OzWJiIHcQl+0/ryAo/goBvgchnyqJ0Z7BfglfM9Bp133IWDsJshPhD743clA4jsOmrL61YT40Ac6w7mFBrROsVgEyx0S2Shs7Q8y+kBf8DOnumQDBnoedBQDlKyMgOxtyG7he8DKwL+oDQkA71saavn3Apj7JOY+LoFiUGYBvHWg7/BzkZXRF2yMbsuvCAz2AydD521R+gos4qQ2KFj5JvAGNS/gfgYRQfiAuxLfH2kDfxv5T6DlmqfhfCoqWn4qZLXGk46qAvPFiAT7kcBEfnkTvLe0YkCFIObb2tqeg6zB5isN3vY4evV1dXWPo5lD7l0Kx9fyOFpdDdoXAkTbQLdAPVoH7cONjY3Pap4G7aZvlp8IGilBHIrSd2FER6BzxAYR7U8wxotaNyAliHnnj//3zif1MzB2mVZgmQT+KOiqXA6XQXtin27+BJ3V+hbo08oTwt9y6Z2w/kHnG922gP4kfbP8RMhOYq5baWUaNAx6f5ughCPOMqgMNojcWRhnO4L+slLjDr/m1G5GvwNOnQz2Q7vEPAXZe6DNt7uXA7p9kcp1zpcu+qRxznVBngTnF2skqhDoadTX1z8GxYOgYx0dHYutXIGTDjEgoAuBGXanHLcy6CBy9+L3vtDW4Bgy9rRj8ntW0ieP4810SoHYtN/yZczfePK4GAVfWKdCbEr1bQbqiFZU5go6KVdAWwI/HJW0vjqIkjbOh7aGk1zr5ILCtwQ6pR2lHONtuN0rGdDrBB1O4HPMKYz5LsZZb+UWLkNcAsJlUVEZk24TJ3/lhRD489mJ+DY4f0TKghj0QF+J7lbnL4OPcPE0x768GsvyknD+IuExtHzmWM5xGnTIyi2gc8xV8G0WWApA+ewcNxVfLCWTy2aCyF2m+QHzPc5hh+D3XtAboI+lz3CU4elJQHcwaaeB3wO6znlAE1Zu4fyCH2TKs7JEQPkmJj5nSgfeou+AJllaKP4sQL4xqd6SfDtdf0aSnOWC2Il5Xg96wrvh1MXi/G1K3s+gYfaBfZuLvgpITPTy0uCT7QrsWWXlBMbopz0uw60LnX+SFiMVnBSdLjlfUuzgJKDfhTfXLdZjJ5PdTWMDTTKZUyZBuwj6o+ALYb7RX9L90X7f9Ne02x5ryc1Wr1PrBD3YehTzvmZlFuhfQuXyguXPhbyUEP2g1aA4Sll1DXFgH4+rlVVATnZOQ0LOYZ6+LLt7Zn7aA/4u58uxsifmQoK+cIHtK6eqgGMTd7JqSWB+jVNKGV4yzj/Hpi+gaoG+VHuhyoAJT8aV392ZwdXneEnPQQSvF3Q1zlDq3AVy9CXhhFQfcG4N6BdzOd0p8nDkFYz3mfOPgfNor0d51WIVFxK03fkSKPG/gHsC2Slz3nz/RXR1dT3sfH3aa2U11FBDDTVkw78IhJgI0vL2CQAAAABJRU5ErkJggg==>

[image3]: <data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB0AAAAZCAYAAADNAiUZAAABvUlEQVR4Xu1UPUsDQRC9Q6z8LIzB3CV3SU5CBD/gENFKRMVGsBHsxMZC8gcEO3sLsQqCWFlZ2FsEBBtbU9kkjYIgQiBpBOMbmTPDemEPjKCQB4+bnXm7b25v9wzjv8N13WFwx7btccdxxiimnKrrKMgIPIXRBrio1n8FbHqo5qPAxPZ4alLAzGazo1h8HnGPLLDpUSqV2sXz0vO8QVkPgwnxBLblChMqapGAmovaLXgPFsEHpGaCOptep9PpKR6XLcuyWysI+L7fG4vF+mHqQ1gHq6oGuQL4Ds2yyOXBF/AEQxNmCJ0FirleRVPngT4UGtMSG+RFjt6sCpYTicQIGSB+xeeZ5DrVjlurhEBj+sSLjAU52h1ups5zD8A9o/WmNeRXvhYJg8b0M9/GtIm565lMZghxkQ4SH6aCwQ20hca0qTOV+sj4i6ba7ZX6yNCYfjtIuVxuAOMbsJFMJmelPjI0pndgDXdxWuSCK1PBNbGkPipM3LM1LPAGPtNYFunXiPwjGjujnwnloN+nJvGck9pI4I6bISzRdxO6JWoIvIDRFp4NNLFp6K7FTxGPx/uwxasw3aZYrXfRRRcdxwfuUpewHpuqbgAAAABJRU5ErkJggg==>

[image4]: <data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADsAAAAaCAYAAAAJ1SQgAAAD20lEQVR4Xu1XS0iUURT+Bw3s/bRJZ5w7owMmBRWz6rEwKAiigmpnuxYtlBZCRZtw4zIwk4geRIvoQZsgI8pFtChhVoHmKjApIkKEQMlKp+/z3jveOf3z0HGmFvPBx//fc869557zn/v4Pa+C/wpVSqnD4DWwF+2ANPhnaGxsXJtIJJZJ+WKBAEej0egZ06xmOxwOh6ye/ux7UeCkY7FYEA7qamtrV0m9BOw6wKtLHOxX8LLTnoxEIgnbRiKeQHbctheDAAZ4C05h4DE8P4G/8b5XGrqATbKpqWmzlGNC61iGZqwPeF5yEwJ9DeS94G3whuE5yuvr61fApMqYcl6cS8z2xcdAU70DT1hZwQiFQmFmCzzmzTvxUDobMOBMtkGhjyOIg1JOBIPBlUqvu89gCpwGdzsm1fDXyiRAPgSeBvd4Yn1Cvw087yM/BfsRBu7KcwIOd5rsJ6WOMBOZAHcJVQB9exDwciHPAPq9Ad+bgPs8MWl8xU0NDQ3bXZkF1yb6vPScDyB0g5yDV8gGBsPXnASzJHUW0B0xE03ifb2VK71Wv7i2foBNm9kDRsw4HVLvtg1Yuh3wd9K8t2OMHdKISYJuIjq/mWWHcT6Ya3dzgv0I1lFm1ls/OCDtXTA5sGnhO/p0WX+OSQA2d5z2HFi2sLvJYEn0fcGE+dhx/CT4WOoyAAOucjrPyLQE9J3GLh0sn6Z9S9q7gL7FVoP9CuCs1ZvJPpvvoQHZd+PTcoB7gLTz9Fe/Bw5LRQZg0Ebn2daLBTNvHKbLGM+E0sfBBWnvgj6cJs/L+xyL7xSYcbgmFw307wbHpTwNnp8weMWseHkWN2xmOUEk5aiV2dLm07V14ffVnE2lyzMlrIo8L5lwzlHK07DBwuldqRNgmaQ4QXddFxIs9C0yWCPnxjYC31upp520WQhMsKwWf9gNJl+wpsxmIuIsLTBYLpO/1rQyewV8X8HzaXNz82ppsxCYYKekPANK1zoDrpE6gl+fu2DE/0Dfh76/wE5X7kLp25HfsUJdypCX/KJggp2Ucom5EoXxA3eni8fja/jFofsB3Vm3gwUvAtAPK73mM4Db2Eb0vwjdN3C/1BNKb1TjqsgSthWq8hyBc1B6/UwpfYx0o/NDPH+Cj5RzF/WB3Vzkls9fs5RLv/MRfg6xagr50cgF/gnBxyjnLnW+YHbAVnRo47PQCXB3Rp9pKS8nkPADSp/J7p176cE/HTgZkvIygsuwDwE/z3c/XxJE9J9HrnIvGSL6b2hMnhQlBdeeyvILWCrQH9if605fEiDYLcjudf4TS12pAJ89ZQ+0ggoqKAv+AO3AGeTGueTdAAAAAElFTkSuQmCC>

[image5]: <data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACsAAAAaCAYAAAAue6XIAAACwUlEQVR4Xu2WPWgUQRTH71BB8QvF88x9ze3dwSFaKCc2itgINmphmXQWWgSLFLFX0gtaWAhiIajYiAREUvhRKKSNjZ0hYGewSNCYqP//7swx/m9vs4u5gHA/eMzte2/evJl9+25yuSH/CY1GY2+n09mm+n7U6/XthUJhl+ozw0WDICgaY0bSBITfOOROlmQR39RqtTfVavWE2tKSx6LvIcsINI9xAbKK36fU0Qc+s81m86DqHZVKZb/qCBI+iRP+xFFtiZTL5QomPodcwuMWp+dCSGYNctlz7wJ7C5s5p3pSLBZ3Yt4VyDe1WXg4tyAzLCM1xoIEj9mTnFUbgX4Osgg5LqY85t5GwjtEzzlf7SZXIb/V7oAt4NqIc01tPcDpLYNhwpjaHLBdoA83g9/7nN5EtfrF91UQ/2FSsgQ+5+GzovoebBIfkl6Dl+xnyAh1/Jrxexoyo/4+aZJF/MZ6mw5fgU1iXG0+sE9oshzt833190mTbLvd3g2fdzwAtXWBwyhkEe3jqNp8sPMHNtluGWDs4HkJ4w3190mTLNgKn2elUumAGkLYP+HwGvIIj3m1+8DnFxfEpi46nSsNjr6vkjJZ53dY9SEuWTqpTWB74an+VdeDSJZvS/UhrA8EmV4vWfu612rSSweRLHu96rsgyJRNOLawefqwvUJCkzkpFehOY+5PyISvV7Ika+zH24/wFWPhx/y3ccpWq7XHTv4O23V/goMfA+wfTVTzsdh/sBdco9+BEBdL9T2YqLEvm6gNTSHoE4wrkKeQQP098rWoS8QuwgTjJK5sbKktqT4W7hpyFhNGOaa5aRF2B8z5ofqsYM2riLOg+g2FNy0sMqf6LPBegZN9iTh31bbhYKExk1wuibDLQOYhR9Q2ENgxTJ8rZAKs+UnIvSyX9n8GyR7iool9UsCF+ww2eHNTEx0yZJP4A8Vfyh41ZK1XAAAAAElFTkSuQmCC>

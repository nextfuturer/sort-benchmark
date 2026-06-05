# **BÁO CÁO ĐỒ ÁN SORT BENCHMARK**

## **1\. THÔNG TIN SINH VIÊN**

* **Tên môn học:** Cấu trúc Dữ liệu và Giải thuật  
* **Thời gian học:** Học kỳ 2, Năm học 2025-2026  
* **Họ tên sinh viên:** Lê Thiên Tấn, Nguyễn Thiên Võ, Phạm Minh Thiện  
* **MSSV:** 25120434, 25120473, 25120441

## **2\. THUẬT TOÁN TỐT NHẤT Ở LẦN CHẠY ĐẦU TIÊN (BENCHMARK 1\)**

Ở lần chạy đầu tiên, ưu tiên hàng đầu của chúng em là hoàn thành sớm và đảm bảo tính đúng đắn của chương trình trên các bộ test cơ bản, đồng thời kiểm soát chặt chẽ giới hạn bộ nhớ (Memory Limit):

* **Bài A (Integer Sort):** Chúng em sử dụng hàm std::sort kết hợp với std::greater\<int\>() để sắp xếp nếu cần.  
  * *Lý do:* Hàm std::sort của C++ cài đặt thuật toán IntroSort (kết hợp QuickSort, HeapSort và InsertionSort). Nó đảm bảo độ phức tạp thời gian luôn ở mức O(N log N) và độ phức tạp không gian chỉ là O(log N), an toàn tuyệt đối trước lỗi tràn bộ nhớ (MLE) cho dù mảng lên tới 10^5 phần tử.  
* **Bài B (Lexicographic Sort):** Tương tự Bài A, chúng em sử dụng std::sort kết hợp Fast I/O (cin.tie(NULL)).  
  * *Lý do:* Việc triển khai một cấu trúc dữ liệu phức tạp như Trie tĩnh mảng 2D cho 10^5 chuỗi (mỗi chuỗi tối đa 100 ký tự) sẽ tiêu tốn khoảng 1GB RAM, dẫn đến việc bị hệ thống chấm rớt ngay lập tức. Hàm sort tích hợp sẵn là phương pháp an toàn nhất.  
* **Bài C (Length-aware Lexicographic Sort):** Chúng em sử dụng std::sort với một hàm so sánh (Comparator) tự định nghĩa.  
  * *Lý do:* Hàm cmp được viết đơn giản: kiểm tra chiều dài bằng hàm .length() trước, nếu bằng nhau thì dùng toán tử \< để so sánh chuỗi. Cách tiếp cận này giúp giải quyết nhanh yêu cầu của đề bài.

## **3\. CÁCH THỨC SINH TEST CASE (VÒNG HACKING)**

Sau khi quan sát các bài nộp Lần 1, chúng em nhận thấy đa số các bạn đều dùng std::sort hoặc QuickSort tự viết. Chương trình test\_gen.cpp được chúng em thiết kế đặc biệt để khai thác triệt để các lỗ hổng của những thuật toán này:

### **Bài A (int): Mục tiêu bẫy QuickSort và Radix Sort cơ bản**

1. **Test 1 (Mảng giảm dần):** Ép QuickSort (nếu cài đặt chọn chốt ở đầu/cuối mảng) rơi thẳng vào trường hợp xấu nhất O(N^2), gây Time Limit Exceeded (TLE).  
2. **Test 2 (Toàn số trùng lặp):** Bẫy các thuật toán phân hoạch không sử dụng kỹ thuật 3-way partitioning. Khi mảng toàn số giống nhau, chúng không thể chia đôi mảng đều đặn, dẫn đến O(N^2).  
3. **Test 3 (Âm/Dương xen kẽ sát mức giới hạn):** Sinh các số gần INT\_MIN và INT\_MAX. Nhắm vào các bạn dùng Radix Sort nhưng xử lý bit dấu sai hoặc ép kiểu bị tràn bộ đệm.  
4. **Test 4 (Mảng V-Shape \- Nửa giảm, nửa tăng):** Thiết kế dữ liệu phá vỡ khả năng phán đoán của Branch Predictor trong CPU, làm chậm quá trình so sánh rẽ nhánh.  
5. **Test 5 (Thuần ngẫu nhiên):** Ép băng thông I/O lên mức cao nhất để kiểm tra khả năng đọc/ghi của chương trình.

### **Bài B (strlexi): Mục tiêu làm quá tải phép so sánh chuỗi của std::sort**

1. **Test 1 (Ngẫu nhiên):** Đánh giá tốc độ xử lý cơ bản trên dải ký tự từ 'a' đến 'z'.  
2. **Test 2 (Tiền tố chung siêu dài):** Đặt 90 ký tự đầu của toàn bộ 10^5 chuỗi giống hệt nhau. Khi dùng operator\< để sort, máy tính phải so sánh lại 90 ký tự vô ích này hàng trăm triệu lần, trực tiếp làm sập (TLE) thuật toán std::sort.  
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
* **Bài C (strlenlexi):** Áp dụng kiến trúc **Hybrid Sort (sort tự chế để sort theo độ dài \+ MSD Radix Sort chuẩn ASCII)**.  
  * *Thay đổi chiến thuật:* Ban đầu chúng em định dùng Trie tĩnh, nhưng nhận ra cấu trúc Trie rất mỏng manh trước các "Test bẩn" (Ví dụ: chứa ký tự lạ ngoài a-z làm âm chỉ số mảng, hoặc nhồi khối lượng node khổng lồ gây tràn RAM). Do đó, chúng em chuyển sang chiến thuật an toàn tuyệt đối.  
  * *Tối ưu:* 1\. Đầu tiên, dùng sort tự chế với hàm Comparator **CHỈ** so sánh chiều dài. Phép so sánh này tốn O(1), chạy cực nhanh và không bao giờ bị TLE.  
    2\. Sau đó, chúng em gom các chuỗi có **cùng chiều dài** thành từng cụm, và đưa cụm đó vào hàm MSD Radix Sort.  
    3\. Hàm Radix Sort được nâng cấp dùng mảng đếm 258 ô (unsigned char), qua đó cover toàn bộ 256 ký tự của bảng mã ASCII, biến code trở nên "bất tử" trước mọi nỗ lực Hacking bằng ký tự lạ, đồng thời không tiêu tốn RAM.  
  * *Tối ưu vi mô cực hạn:* Trong quá trình test thực tế hệ thống Hybrid Sort, chúng em phát hiện mảng std::string khi gán bằng dấu \= trong các vòng đệ quy sẽ gây ra hiện tượng Deep Copy (sao chép sâu), khiến chương trình phải xin cấp phát RAM liên tục và bị TLE (\>10s). Để khắc phục triệt để, chúng em đã áp dụng ngữ nghĩa di chuyển (**Move Semantics**) với hàm std::move() của C++11. Việc này chuyển hóa hoàn toàn Deep Copy thành Pointer Swap (hoán vị con trỏ), giúp triệt tiêu hàng triệu lệnh cấp phát bộ nhớ thừa, ép thời gian chạy từ hơn 10 giây xuống chỉ còn vài chục mili-giây (O(1) cho mỗi phép gán).

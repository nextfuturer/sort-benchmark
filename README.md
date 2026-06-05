# BÁO CÁO ĐỒ ÁN SORT BENCHMARK

## 1. THÔNG TIN SINH VIÊN

* **Tên môn học:** Cấu trúc Dữ liệu và Giải thuật
* **Thời gian học:** Học kỳ 2, Năm học 2025-2026
* **Họ tên sinh viên:** Lê Thiên Tấn, Nguyễn Thiên Võ, Phạm Minh Thiện
* **MSSV:** 25120434, 25120473, 25120441

---

## 2. THUẬT TOÁN Ở LẦN CHẠY ĐẦU TIÊN (BENCHMARK 1) - PHƯƠNG PHÁP NGÂY THƠ (NAIVE SOLUTION)

Ở lần chạy đầu tiên, với mục tiêu làm quen với hệ thống và hoàn thành sớm các trường hợp cơ bản, chúng em đã tiếp cận bài toán bằng các phương pháp ngây thơ (Naive solutions) dựa trên cấu trúc tư duy tuyến tính thuần túy:

* **Bài A (Integer Sort):** Chúng em sử dụng thuật toán sắp xếp dựa trên so sánh cơ bản như QuickSort thông thường chọn phần tử chốt (pivot) ở đầu mảng hoặc Interchange Sort cơ bản.
  * *Lý do:* Đây là cách cài đặt trực quan, dễ viết và chạy tốt với các bộ test ngẫu nhiên phân phối đều ở quy mô nhỏ. Nhóm ưu tiên tính đúng đắn về mặt logic chạy trước tiên.
* **Bài B (Lexicographic Sort):** Chúng em áp dụng phương pháp so sánh trực tiếp cặp chuỗi bằng toán tử `<` lồng trong một thuật toán sắp xếp thông thường.
  * *Lý do:* Phương pháp này lợi dụng trực tiếp bảng mã ASCII có sẵn của ngôn ngữ, không cần xây dựng cấu trúc lưu trữ phức tạp, giúp việc cài đặt mã nguồn diễn ra nhanh chóng.
* **Bài C (Length-aware Lexicographic Sort):** Chúng em thiết kế một hàm so sánh ngây thơ (Naive Comparator): thực hiện đo và so sánh chiều dài chuỗi bằng `.length()` trước, nếu chiều dài bằng nhau thì tiến hành so sánh từ điển bằng toán tử `<`. Hàm này sau đó được nhúng vào cấu trúc vòng lặp sắp xếp cơ bản của mảng.
  * *Lý do:* Cách tiếp cận này bám sát một cách trực diện nhất vào yêu cầu của đề bài đưa ra, giúp giải quyết nhanh trật tự ưu tiên hai lớp (Độ dài trước, từ điển sau).

---

## 3. CÁCH THỨC SINH TEST CASE (VÒNG HACKING)

Sau khi nhận thấy các phương pháp ngây thơ hoặc thuật toán so sánh cơ bản lộ rõ nhiều nhược điểm lớn khi xử lý dữ liệu lớn, chúng em đã thiết kế chương trình `test_gen.cpp` để khai thác triệt để những tử huyệt hiệu năng này:

### Bài A (int): Mục tiêu bẫy QuickSort và Radix Sort cơ bản
1. **Test 1 (Mảng giảm dần):** Ép QuickSort ngây thơ (chọn chốt đầu/cuối mảng) rơi thẳng vào trạng thái tồi nhất với độ phức tạp `O(N^2)`, gây ra lỗi quá thời gian (TLE).
2. **Test 2 (Toàn số trùng lặp):** Bẫy các giải thuật phân hoạch không có kỹ thuật 3-way partitioning, khiến việc chia đôi mảng bị mất cân bằng nghiêm ngặt dẫn đến `O(N^2)`.
3. **Test 3 (Âm/Dương xen kẽ sát mức giới hạn):** Sinh các giá trị cực hạn sát miền `INT_MIN` và `INT_MAX`, nhắm vào những thuật toán Radix Sort xử lý bit dấu sai hoặc ép kiểu lỗi gây tràn bộ nhớ.
4. **Test 4 (Mảng V-Shape - Nửa giảm, nửa tăng):** Thiết kế cấu trúc bẫy khả năng dự đoán rẽ nhánh (Branch Predictor) của CPU, làm chậm tốc độ thực thi phần cứng.
5. **Test 5 (Thuần ngẫu nhiên):** Đẩy băng thông đọc ghi dữ liệu lên tối đa để kiểm tra độ chịu tải I/O.

### Bài B (strlexi): Mục tiêu làm quá tải phép so sánh chuỗi của thuật toán ngây thơ
1. **Test 1 (Ngẫu nhiên):** Kiểm tra tính ổn định nền tảng trên dải ký tự chữ cái phổ thông từ 'a' đến 'z'.
2. **Test 2 (Tiền tố chung siêu dài):** Đặt 90 ký tự đầu của toàn bộ 10^5 chuỗi giống hệt nhau. Khi các thuật toán ngây thơ gọi so sánh từ điển, CPU buộc phải quét lại 90 ký tự trùng lặp này hàng triệu lần một cách vô ích, gây nghẽn cổ chai hệ thống và sập TLE lập tức.
3. **Test 3 (Toàn chuỗi trùng lặp):** Đánh vào lỗi cấp phát đệm thừa hoặc lặp vô hạn của các giải thuật đệ quy chưa hoàn thiện.
4. **Test 4 (Sắp xếp ngược bảng chữ cái):** Đẩy số lượng phép hoán vị (Swap) ô nhớ lên mức kịch trần.
5. **Test 5 (Giới hạn ký tự chỉ 'a' và 'b'):** Tăng xác suất trùng lặp chuỗi con, tạo hiệu ứng bẫy tương tự cấu trúc tiền tố dài.

### Bài C (strlenlexi): Mục tiêu bẫy hàm tính chiều dài ngây thơ
1. **Test 1 (Ngẫu nhiên):** Đảm bảo thuật toán tuân thủ đúng yêu cầu phân loại độ dài trước.
2. **Test 2 (Cùng độ dài tối đa 100, xếp ngược):** Triệt tiêu hoàn toàn lợi thế phân loại theo chiều dài, ép hệ thống phải so sánh chuỗi nguyên vẹn trên dải dữ liệu lớn.
3. **Test 3 (Tiền tố giống nhau, chiều dài ngẫu nhiên xen kẽ):** Buộc bộ so sánh phải liên tục nhảy qua lại giữa việc tính độ dài và so sánh mã ASCII, làm tăng tỷ lệ Cache Miss của CPU.
4. **Test 4 (Sắp xếp ngược chiều dài):** Nhắm vào các thuật toán phân xô cài đặt sai thứ tự duyệt index.
5. **Test 5 (Toàn chuỗi trùng lặp):** Kiểm tra khả năng bảo toàn số lượng bản sao chính xác tuyệt đối.

---

## 4. THUẬT TOÁN TỐT NHẤT Ở LẦN THỨ HAI (BENCHMARK 2)

Nhận thức rõ sự yếu kém của các giải pháp ngây thơ trước những bộ test case hiểm hóc, chúng em đã kiến trúc lại hoàn toàn mã nguồn ở Lần 2 nhằm đạt độ phức tạp tiệm cận tuyến tính và miễn nhiễm với mọi "Test bẩn" (Dirty Data):

* **Bài A (int):** Thay thế bằng **LSD Radix Sort (Cơ số 256) tích hợp Ping-Pong Buffer**.
  * *Tối ưu:* Thuật toán sắp xếp 4 lần (mỗi lần 8-bit). Kỹ thuật Ping-Pong Buffer (luân chuyển dữ liệu tĩnh giữa hai mảng qua tham chiếu) giúp loại bỏ hoàn toàn các lệnh copy mảng `a = ketqua` tốn kém. Việc xử lý số âm được thực hiện bằng phép đảo bit dấu `XOR 0x80000000` (nhanh hơn nhiều so với phép chia hệ thập phân).

* **Bài B (strlexi):** Thay thế bằng **MSD Radix Sort (In-place ảo)**.
  * *Tối ưu:* Để giải quyết bẫy "Tiền tố dài" mà không bị tràn bộ nhớ (MLE) như khi dùng Trie tĩnh, MSD Radix Sort mô phỏng lại logic rẽ nhánh của Trie bằng cách chia xô (Bucketing) đệ quy ngay trên mảng. Nó phân loại chuỗi theo từng cột ký tự, triệt tiêu hoàn toàn việc so sánh lại các đoạn tiền tố đã giống nhau.

* **Bài C (strlenlexi):** Áp dụng kiến trúc **Hybrid Sort (Sắp xếp theo độ dài + MSD Radix Sort chuẩn ASCII)**.
  * *Thay đổi chiến thuật:* Ban đầu chúng em định dùng Trie tĩnh, nhưng nhận ra cấu trúc Trie rất mỏng manh trước các "Test bẩn" (Ví dụ: chứa ký tự lạ ngoài a-z làm âm chỉ số mảng, hoặc nhồi khối lượng node khổng lồ gây tràn RAM). Do đó, chúng em chuyển sang chiến thuật an toàn tuyệt đối.
  * *Tối ưu:* 1. Đầu tiên, thực hiện sắp xếp mảng chỉ dựa trên khóa độ dài. Phép so sánh chiều dài số nguyên tốn `O(1)`, chạy cực nhanh và không bị bẫy bởi nội dung ký tự.
    2. Sau đó, chúng em cô lập và gom các chuỗi có **cùng chiều dài** thành từng cụm, rồi đưa cụm đó vào hàm MSD Radix Sort. 
    3. Hàm Radix Sort được nâng cấp dùng mảng đếm 258 ô (`unsigned char`), qua đó cover toàn bộ 256 ký tự của bảng mã ASCII, biến code trở nên "bất tử" trước mọi nỗ lực Hacking bằng ký tự lạ, đồng thời không tiêu tốn RAM.
  * *Tối ưu vi mô cực hạn:* Trong quá trình test thực tế hệ thống Hybrid Sort, chúng em phát hiện mảng `std::string` khi gán bằng dấu `=` trong các vòng đệ quy sẽ gây ra hiện tượng Deep Copy (sao chép sâu), khiến chương trình phải xin cấp phát RAM liên tục và bị TLE (>10s). Để khắc phục triệt để, chúng em đã áp dụng ngữ nghĩa di chuyển (**Move Semantics**) với hàm `std::move()` của C++11. Việc này chuyển hóa hoàn toàn Deep Copy thành Pointer Swap (hoán vị con trỏ), giúp triệt tiêu hàng triệu lệnh cấp phát bộ nhớ thừa, ép thời gian chạy từ hơn 10 giây xuống chỉ còn vài chục mili-giây (`O(1)` cho mỗi phép gán).

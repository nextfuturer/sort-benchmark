BÁO CÁO ĐỒ ÁN SORT BENCHMARK
1. THÔNG TIN SINH VIÊN
Tên môn học: Cấu trúc Dữ liệu và Giải thuật
Thời gian học: Học kỳ 2, Năm học 2025-2026
Họ tên sinh viên: Lê Thiên Tấn
MSSV: 2512043
2. THUẬT TOÁN TỐT NHẤT Ở LẦN CHẠY ĐẦU TIÊN (BENCHMARK 1)
Ở lần chạy đầu tiên, ưu tiên hàng đầu của em là hoàn thành sớm và đảm bảo tính đúng đắn của chương trình trên các bộ test cơ bản, đồng thời kiểm soát chặt chẽ giới hạn bộ nhớ (Memory Limit):
Bài A (Integer Sort): Em sử dụng hàm std::sort kết hợp với std::greater<int>() để sắp xếp nếu cần.
Lý do: Hàm std::sort của C++ cài đặt thuật toán IntroSort (kết hợp QuickSort, HeapSort và InsertionSort). Nó đảm bảo độ phức tạp thời gian luôn ở mức  và độ phức tạp không gian chỉ là , an toàn tuyệt đối trước lỗi tràn bộ nhớ (MLE) cho dù mảng lên tới  phần tử.
Bài B (Lexicographic Sort): Tương tự Bài A, em sử dụng std::sort kết hợp Fast I/O (cin.tie(NULL)).
Lý do: Việc triển khai một cấu trúc dữ liệu phức tạp như Trie tĩnh mảng 2D cho  chuỗi (mỗi chuỗi tối đa 100 ký tự) sẽ tiêu tốn khoảng 1GB RAM, dẫn đến việc bị hệ thống chấm rớt ngay lập tức. Hàm sort tích hợp sẵn là phương pháp an toàn nhất.
Bài C (Length-aware Lexicographic Sort): Em sử dụng std::sort với một hàm so sánh (Comparator) tự định nghĩa.
Lý do: Hàm cmp được viết đơn giản: kiểm tra chiều dài bằng hàm .length() trước, nếu bằng nhau thì dùng toán tử < để so sánh chuỗi. Cách tiếp cận này giúp giải quyết nhanh yêu cầu của đề bài.
3. CÁCH THỨC SINH TEST CASE (VÒNG HACKING)
Sau khi quan sát các bài nộp Lần 1, em nhận thấy đa số các bạn đều dùng std::sort hoặc QuickSort tự viết. Chương trình test_gen.cpp được em thiết kế đặc biệt để khai thác triệt để các lỗ hổng của những thuật toán này:
Bài A (int): Mục tiêu bẫy QuickSort và Radix Sort cơ bản
Test 1 (Mảng giảm dần): Ép QuickSort (nếu cài đặt chọn chốt ở đầu/cuối mảng) rơi thẳng vào trường hợp xấu nhất , gây Time Limit Exceeded (TLE).
Test 2 (Toàn số trùng lặp): Bẫy các thuật toán phân hoạch không sử dụng kỹ thuật 3-way partitioning. Khi mảng toàn số giống nhau, chúng không thể chia đôi mảng đều đặn, dẫn đến .
Test 3 (Âm/Dương xen kẽ sát mức giới hạn): Sinh các số gần INT_MIN và INT_MAX. Nhắm vào các bạn dùng Radix Sort nhưng xử lý bit dấu sai hoặc ép kiểu bị tràn bộ đệm.
Test 4 (Mảng V-Shape - Nửa giảm, nửa tăng): Thiết kế dữ liệu phá vỡ khả năng phán đoán của Branch Predictor trong CPU, làm chậm quá trình so sánh rẽ nhánh.
Test 5 (Thuần ngẫu nhiên): Ép băng thông I/O lên mức cao nhất để kiểm tra khả năng đọc/ghi của chương trình.
Bài B (strlexi): Mục tiêu làm quá tải phép so sánh chuỗi của std::sort
Test 1 (Ngẫu nhiên): Đánh giá tốc độ xử lý cơ bản trên dải ký tự từ 'a' đến 'z'.
Test 2 (Tiền tố chung siêu dài): Đặt 90 ký tự đầu của toàn bộ  chuỗi giống hệt nhau. Khi dùng operator< để sort, máy tính phải so sánh lại 90 ký tự vô ích này hàng trăm triệu lần, trực tiếp làm sập (TLE) thuật toán std::sort.
Test 3 (Toàn chuỗi trùng lặp): Khai thác lỗi cấp phát bộ nhớ dư thừa hoặc lặp vô tận ở các thuật toán đệ quy chưa hoàn thiện.
Test 4 (Sắp xếp ngược bảng chữ cái): Đẩy số lượng phép hoán vị (Swap) trong bộ nhớ lên mức kịch trần.
Test 5 (Giới hạn ký tự chỉ 'a' và 'b'): Làm tăng xác suất trùng lặp các đoạn nhỏ trong chuỗi, tạo ra hiệu ứng nghẽn cổ chai tương tự Test 2.
Bài C (strlenlexi): Mục tiêu bẫy hàm tính chiều dài length()
Test 1 (Ngẫu nhiên): Đảm bảo thuật toán tuân thủ đúng yêu cầu sắp xếp theo độ dài trước.
Test 2 (Cùng độ dài tối đa 100, xếp ngược): Loại bỏ lợi thế phân loại theo chiều dài, ép hệ thống phải so sánh chuỗi nguyên vẹn trên mảng lớn.
Test 3 (Tiền tố giống nhau, chiều dài ngẫu nhiên xen kẽ): Buộc hàm cmp của đối thủ phải liên tục nhảy qua lại giữa việc đếm ký tự và so sánh mã ASCII, làm mất hiệu suất của Cache CPU.
Test 4 (Sắp xếp ngược chiều dài): Nhắm vào các thuật toán Bucket Sort cài đặt sai thứ tự duyệt index các xô.
Test 5 (Toàn chuỗi trùng lặp): Đảm bảo tính ổn định của việc in ra đủ số lượng bản sao.
4. THUẬT TOÁN TỐT NHẤT Ở LẦN THỨ HAI (BENCHMARK 2)
Nhận thức được sự yếu kém của std::sort trước các "bẫy" dữ liệu do chính mình và các bạn thiết kế, em đã thiết kế lại toàn bộ kiến trúc thuật toán ở Lần 2 nhằm đạt được độ phức tạp tuyến tính O(N) và miễn nhiễm với mọi Test Case:
Bài A (int): Thay thế bằng LSD Radix Sort (Cơ số 256) tích hợp Ping-Pong Buffer.
Tối ưu: Thuật toán sắp xếp 4 lần (mỗi lần 8-bit). Kỹ thuật Ping-Pong Buffer (luân chuyển dữ liệu tĩnh giữa hai mảng qua tham chiếu) giúp loại bỏ hoàn toàn các lệnh copy mảng a = ketqua tốn kém. Việc xử lý số âm được thực hiện bằng phép đảo bit dấu XOR 0x80000000 (nhanh hơn nhiều so với phép chia hệ thập phân).
Bài B (strlexi): Thay thế bằng MSD Radix Sort (In-place ảo).
Tối ưu: Để giải quyết bài toán "Tiền tố dài" mà không bị tràn bộ nhớ (MLE) như khi dùng Trie mảng 2D, MSD Radix Sort mô phỏng lại logic rẽ nhánh của Trie bằng cách chia xô (Bucketing) đệ quy ngay trên mảng. Nó phân loại chuỗi theo từng cột ký tự, loại bỏ hoàn toàn việc phải so sánh lại các đoạn tiền tố đã giống nhau, và chỉ dùng thêm một mảng tạm không đáng kể.
Bài C (strlenlexi): Áp dụng Bucket Sort kết hợp Cây Tiền Tố (Trie) mảng tĩnh.
Tối ưu: Dữ liệu được ném thẳng vào 101 xô (Bucket) dựa trên chiều dài, triệt tiêu phép đo .length(). Khi duyệt từng xô, chuỗi được nạp vào Trie và duyệt DFS để in, triệt tiêu phép so sánh từ điển.
Tối ưu vi mô: Để tái sử dụng Trie tĩnh (tránh MLE) mà không bị làm chậm bởi lệnh memset, em áp dụng kỹ thuật Lazy Reset (Selective Clearing): Chỉ dùng vòng lặp xóa 0 tại các node thực sự đã được cấp phát (nodeCount) ở xô liền trước.

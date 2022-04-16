# Lisseq

Khỏe là 1 lực sĩ rất mạnh. Sau màn biểu diễn "Một tay nâng 15 người" nổi tiếng, Khỏe đã lấn sân sang bộ môn cử tạ.

Khỏe có $n$ quả tạ. Quả tạ thứ $i$ nặng $k_i$ kg. Mỗi ngày Khỏe chọn ra 1 **dãy con tăng dần dài nhất** các quả tạ để biểu diễn. Để màn biểu diễn không nhàm chán, không có 2 ngày nào Khỏe chọn cùng 1 dãy con các quả tạ. Sau $T$ ngày biểu diễn, Khỏe đã hết cách chọn hợp lệ và quyết định chuyển sang biểu diễn vác *Lu nước*.

![](lisseq1.jpeg)

Vì muốn tập thể thao để có thể cường tráng như Khỏe, bạn quyết định xin Khỏe chỗ tạ đó về. Khỏe trả lời:

"Để lấy được chỗ tạ này về, bạn hãy đoán xem cân nặng của những quả tạ này là gì nhé!"

## Input

Bài có nhiều test.

Dòng duy nhất của input chứa 3 số $L, R, N$.

## Output

Với mỗi $T$ từ $L$ đến $R$, bạn phải in ra dãy cân nặng có độ dài $N$ thỏa mãn: Khỏe có thể biểu diễn $T$ ngày với dãy quả tạ có cân nặng đó. Nếu có nhiều đáp án, in bất kỳ.

## Giới hạn
- $L, R \leq 1,000,000,000$, $R=L+99$.
- $N=100$.
- Khối lượng các quả tạ phải từ $0$ đến $100$.

## Subtask
- Subtask 1 (15% số điểm): $L, R \leq 1,000$.
- Subtask 2 (30% số điểm): $L, R \leq 50,000$.
- Subtask 3 (55% số điểm): Không có điều kiện gì thêm.

## Sample

### Input
```
3 5 5
```

### Output
```
2 1 0 3 4 
3 2 1 0 4
1 1 1 1 1
```
**Lưu ý:** Test ví dụ không thỏa mãn giới hạn chuẩn.
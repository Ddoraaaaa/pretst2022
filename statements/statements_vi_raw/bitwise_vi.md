# Bitwise

"Ồ! Mình biết bạn đấy. Một năm trước..."

Xem xong video quảng cáo, bạn lập tức mở máy tính và tải ứng dụng Banana. Nhưng nó không đơn giản như vậy. Bật ứng dụng lên, đập vào mắt bạn là vô vàn các dòng lệnh...

![](bitwise1.png)

Sau khi đọc xong 5,000 trang hướng dẫn, bạn biết ứng dụng hoạt động như sau:

- Mỗi *mã lệnh* thuộc 1 trong 3 loại: `AND val/OR val/XOR val`. 
- Nếu hiện tại bạn đang có $k$ *Mảnh xu*, sau khi *áp mã lệnh*, bạn sẽ có $k$ `AND/OR/XOR` $val$ *Mảnh xu*, với `AND/OR/XOR` là thao tác nhị phân tương ứng với *mã lệnh* đó.
- Giả sử tại phiên ngày hôm nay đang có một dãy gồm $N$ *mã lệnh*. Bạn có thể *lướt sóng* bằng cách duyệt lần lượt các *mã lệnh* từ trái sang phải, đến mỗi *mã lệnh* bạn có thể chọn *áp mã lệnh* đó vào số *Mảnh xu* hiện tại của bạn. Tổng cộng có $2^N$ cách lướt sóng khác nhau.

Ban đầu dãy *mã lệnh* rỗng. Bạn sẽ sử dụng ứng dụng Banana trong $Q$ ngày. Mỗi ngày có 1 trong 3 sự kiện sau:

- `TYPE val` (`TYPE` $\in \{“$`AND`$”, “$`OR`$”, “$`XOR`$”\}$) - thêm 1 *mã lệnh* có dạng `TYPE val` vào cuối dãy *mã lệnh*.
- `REMOVE` - xóa *mã lệnh* ở cuối dãy khỏi dãy.
- `QUERY val`- Giả sử đầu phiên bạn có $0$ *mảnh xu*. Bạn cần đếm xem có bao nhiêu cách *lướt sóng* ngày hôm nay sao cho đến cuối phiên bạn có đúng `val` *mảnh xu*.

## Input

- Dòng đầu chứa số $Q$ - số ngày bạn sử dụng ứng dụng.
- $Q$ dòng sau, mỗi dòng chứa 1 sự kiện.

## Output

Với mỗi sự kiện `QUERY`, bạn hãy in ra đáp án cho truy vấn đó trên 1 dòng. Kết quả có thể rất lớn, bạn hãy in số dư khi chia $1,000,000,007$.

## Giới hạn
- $Q \leq 10,000$
- $val < 2^{14}$

## Subtask
- Subtask 1 (25% số điểm): $Q \leq 500$.
- Subtask 2 (25% số điểm): Không có mã lệnh `AND` và `OR`.
- Subtask 3 (25% số điểm): Không có mã lệnh `AND` và `XOR`.
- Subtask 4 (25% số điểm): Không có điều kiện gì thêm.

## Sample

### Input
```
8
XOR 5
XOR 2
QUERY 7
AND 1
QUERY 1
REMOVE
OR 2
QUERY 2
```

### Output
```
1
2
3
```
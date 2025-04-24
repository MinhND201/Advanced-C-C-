#include <stdio.h>
#include <string.h>

/* kiểu dữ liệu struct chứa dữ liệu của sinh viên gồm có tên, điểm trung bình và ID */
typedef struct  
{
    char ten[50];
    float diemTrungBinh;
    int id;
} SinhVien;

int stringCompare(const char *str1, const char *str2) /*đầu vào là const ptr => con trỏ không thể thay đổi giá trị tại địa chỉ mà nó trỏ đến => đảm bảo ko bị thay đổi dữ liệu*/
{
    while (*str1 && (*str1 == *str2)) /*so sánh 2 string cho đến khi giá trị ký tự khác nhau, đảm bảo chạy while duyệt từng ký tự đến khi *str1 == '\0' tức hết string 1 */
    {
        str1++;
        str2++;
    }
    return (*(const unsigned char*)str1 - *(const unsigned char*)str2);/*đảm bảo chuyển ký tự signed thành giá trị trong 0~255 , 
                                                                        trả về kết quả so sánh < 0 thì *str1 đứng trước *str2
                                                                        =0 thì giống nhau, >0 thì *str1 đứng sau *str2 */
}


// Hàm so sánh theo tên
int compareByName(const void *a, const void *b)/*ép kiểu để so sánh tên trong sv1 và sv2*/
{
    SinhVien *sv1 = (SinhVien *)a;
    SinhVien *sv2 = (SinhVien *)b;
    return stringCompare(sv1->ten, sv2->ten);/*trả về so sánh theo tên*/
}

// Hàm so sánh theo điểm trung bình
int compareByDiemTrungBinh(const void *a, const void *b)
{
    SinhVien *sv1 = (SinhVien *)a;
    SinhVien *sv2 = (SinhVien *)b;
    if (sv1->diemTrungBinh > sv2->diemTrungBinh) return 1;/*trả về so sánh theo điểm*/
    return 0;
}

// Hàm so sánh theo ID
int compareByID(const void *a, const void *b)
{
   SinhVien *sv1 = (SinhVien *)a;
   SinhVien *sv2 = (SinhVien *)b;
   return sv1->id - sv2->id;/*trả về so sánh theo ID*/
}

// Hàm sắp xếp chung
/*Duyệt mảng nhiều lượt .

Trong mỗi lượt, so sánh từng cặp phần tử kề nhau (a[j], a[j+1]).

Nếu a[j] > a[j+1], hoán đổi hai phần tử đó.

Sau lượt i, phần tử lớn nhất trôi về cuối mảng.

Lặp lại cho đến khi không còn hoán đổi nào (mảng đã sắp xếp) hoặc đã thực hiện đủ n–1 lượt.*/
void sort(SinhVien array[], size_t size, int (*compareFunc)(const void *, const void *))/*truyền vào mảng struct sinhvien , length, và function pointer dể linh hoạt dùng các hàm compare*/
{
    for (int i=0; i<size-1; i++)
    {
        for (int j=0; j<size-i-1; j++)
        {
            if (compareFunc(array+j, array+j+1)>0)
            {
                SinhVien temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }        
}

void display(SinhVien *array, size_t size)
{
   for (size_t i = 0; i < size; i++)
   {
       printf("ID: %d, Ten: %s, Diem Trung Binh: %.2f\n", array[i].id, array[i].ten, array[i].diemTrungBinh);
   }
   printf("\n");
}

int main() {
    SinhVien danhSachSV[] =
    {
        {  
            .ten = "Hoang",
            .diemTrungBinh = 7.5,
            .id = 100
        },
        {
            .ten = "Tuan",
            .diemTrungBinh = 4.5,
            .id = 101
        },
        {
            .ten = "Vy",
            .diemTrungBinh = 6.8,
            .id = 102},
        {  
            .ten = "Ngan",
            .diemTrungBinh = 5.6,
            .id = 10
        },
    };

    size_t size = sizeof(danhSachSV) / sizeof(danhSachSV[0]);/*tính length của mảng*/

    // Sắp xếp theo tên
    sort(danhSachSV, size, compareByName);
    display(danhSachSV, size);

    // Sắp xếp theo điểm trung bình
    sort(danhSachSV, size, compareByDiemTrungBinh);
    display(danhSachSV, size);

    // Sắp xếp theo ID
    sort(danhSachSV, size, compareByID);
    display(danhSachSV, size);

    return 0;
}

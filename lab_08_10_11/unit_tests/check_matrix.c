#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "check_matrix.h"
#include "matrix.h"
#include "errors.h"
#include "utils.h"
#include "matrix_operations.h"

double **unit_allocate_matrix(size_t n, size_t m)
{
    double **matrix = malloc(n * sizeof(double *) + n * m * sizeof(double));

    for (size_t i = 0; i < n; i++)
        matrix[i] = (double *)((char *)matrix + n * sizeof(double *) + i * m * sizeof(double));

    return matrix;
}

START_TEST(test_ctrate_matrix_null)
{
    FILE *f = tmpfile();

    int rc = create_matrix(f, NULL);

    ck_assert_int_eq(rc, ERROR_EMPTY_PTR);
}
END_TEST

START_TEST(test_ctrate_matrix_str_size)
{
    FILE *f = tmpfile();
    fprintf(f, "abc cda\n");
    rewind(f);
    struct matrix matrix = { .data=NULL, .row=0, .col=0, .ptr_free=NULL };

    int rc = create_matrix(f, &matrix);

    ck_assert_int_eq(rc, ERROR_INVALID_SIZE);
}
END_TEST

START_TEST(test_ctrate_matrix_negative_size)
{
    FILE *f = tmpfile();
    fprintf(f, "%d %d\n", -12, 0);
    rewind(f);
    struct matrix matrix = { .data=NULL, .row=0, .col=0, .ptr_free=NULL };

    int rc = create_matrix(f, &matrix);

    free(matrix.ptr_free);
    ck_assert_int_eq(rc, ERROR_INVALID_RANGE);
}
END_TEST

START_TEST(test_ctrate_matrix_invalid_el_matrix)
{
    FILE *f = tmpfile();
    fprintf(f, "2 3 3 4 2 abc 2 3\n");
    rewind(f);
    struct matrix matrix = { .data=NULL, .row=0, .col=0, .ptr_free=NULL };

    int rc = create_matrix(f, &matrix);
    
    ck_assert_int_eq(rc, ERRROR_INVALID_EL);
}
END_TEST

START_TEST(test_addition_matrix_NULL_res)
{

    struct matrix matrix1 = {.row=1, .col=1};
    struct matrix matrix2 = {.row=1, .col=1};

    matrix1.data = unit_allocate_matrix(matrix1.row, matrix1.col);
    matrix2.data = unit_allocate_matrix(matrix2.row, matrix2.col);

    int rc;

    rc = addition_matrix(&matrix1, &matrix2, NULL);

    free(matrix1.data);
    free(matrix2.data);

    ck_assert_int_eq(rc, ERROR_EMPTY_PTR);
}
END_TEST

START_TEST(test_addition_matrix_invalid_range)
{
    struct matrix matrix1 = {.row=1, .col=1};
    struct matrix matrix2 = {.row=2, .col=2};
    struct matrix matrix_res = {.data=NULL};

    matrix1.data = malloc(matrix1.row * sizeof(double*));
    matrix2.data = malloc(matrix2.row * sizeof(double*));

    int rc;

    rc = addition_matrix(&matrix1, &matrix2, &matrix_res);

    free(matrix1.data);
    free(matrix2.data);
    free(matrix_res.data);

    ck_assert_int_eq(rc, ERROR_RANGE_SUM);
}
END_TEST

START_TEST(test_addition_matrix_sum_zero_matrix)
{
    struct matrix matrix1 = {.row=2, .col=2};
    struct matrix matrix2 = {.row=2, .col=2};
    struct matrix matrix_res = {.data=NULL};
    
    int rc;

    matrix1.data = unit_allocate_matrix(matrix1.row, matrix1.col);
    matrix2.data = unit_allocate_matrix(matrix2.row, matrix2.col);

    double matrix1_in[][2] = {{1, 1}, {1, 1}};
    double matrix2_in[][2] = {{0, 0}, {0, 0}};
    double matrix_res_out[][2] = {{1, 1}, {1, 1}};

    for (size_t i = 0; i < matrix1.row; i++)
        for (size_t j = 0; j < matrix1.col; j++)
            matrix1.data[i][j] = matrix1_in[i][j];

    for (size_t i = 0; i < matrix2.row; i++)
        for (size_t j = 0; j < matrix2.col; j++)
            matrix2.data[i][j] = matrix2_in[i][j];

    rc = addition_matrix(&matrix1, &matrix2, &matrix_res);

    ck_assert_int_eq(rc, OK);

    for (size_t i = 0; i < matrix_res.row; i++)
        for (size_t j = 0; j < matrix_res.col; j++)
            ck_assert_double_eq(matrix_res_out[i][j], matrix_res.data[i][j]);

    free(matrix1.data);
    free(matrix2.data);
    free(matrix_res.data);
}
END_TEST

START_TEST(test_create_matrix)
{
    FILE *f = tmpfile();
    fprintf(f, "2 2\n");
    fprintf(f, "1 1\n");
    fprintf(f, "2 2\n");
    rewind(f);

    struct matrix matrix;
    int rc = create_matrix(f, &matrix);
    free_matrix(&matrix);
    
    ck_assert_int_eq(rc, OK);
}
END_TEST

START_TEST(test_addition_matrix_reactangle)
{
    struct matrix matrix1 = {.row=2, .col=3};
    struct matrix matrix2 = {.row=2, .col=3};
    struct matrix matrix_res = {.data=NULL};
    
    int rc;

    matrix1.data = unit_allocate_matrix(matrix1.row, matrix1.col);
    matrix2.data = unit_allocate_matrix(matrix2.row, matrix2.col);

    double matrix1_in[][3] = {{1, 1, 1}, {1, 1, 1}};
    double matrix2_in[][3] = {{2, 2, 2}, {2, 2, 2}};
    double matrix_res_out[][3] = {{3, 3, 3}, {3, 3, 3}};

    for (size_t i = 0; i < matrix1.row; i++)
        for (size_t j = 0; j < matrix1.col; j++)
            matrix1.data[i][j] = matrix1_in[i][j];

    for (size_t i = 0; i < matrix2.row; i++)
        for (size_t j = 0; j < matrix2.col; j++)
            matrix2.data[i][j] = matrix2_in[i][j];

    rc = addition_matrix(&matrix1, &matrix2, &matrix_res);

    ck_assert_int_eq(rc, OK);

    for (size_t i = 0; i < matrix_res.row; i++)
        for (size_t j = 0; j < matrix_res.col; j++)
            ck_assert_double_eq(matrix_res_out[i][j], matrix_res.data[i][j]);

    free(matrix1.data);
    free(matrix2.data);
    free(matrix_res.data);
}
END_TEST

START_TEST(test_addition_matrix_single)
{
    struct matrix matrix1 = {.row=1, .col=1};
    struct matrix matrix2 = {.row=1, .col=1};
    struct matrix matrix_res = {.data=NULL};
    
    int rc;

    matrix1.data = unit_allocate_matrix(matrix1.row, matrix1.col);
    matrix2.data = unit_allocate_matrix(matrix2.row, matrix2.col);

    double matrix1_in[][1] = {{1}};
    double matrix2_in[][1] = {{2}};
    double matrix_res_out[][1] = {{3}};

    for (size_t i = 0; i < matrix1.row; i++)
        for (size_t j = 0; j < matrix1.col; j++)
            matrix1.data[i][j] = matrix1_in[i][j];

    for (size_t i = 0; i < matrix2.row; i++)
        for (size_t j = 0; j < matrix2.col; j++)
            matrix2.data[i][j] = matrix2_in[i][j];

    rc = addition_matrix(&matrix1, &matrix2, &matrix_res);

    ck_assert_int_eq(rc, OK);

    for (size_t i = 0; i < matrix_res.row; i++)
        for (size_t j = 0; j < matrix_res.col; j++)
            ck_assert_double_eq(matrix_res_out[i][j], matrix_res.data[i][j]);

    free(matrix1.data);
    free(matrix2.data);
    free(matrix_res.data);
}
END_TEST

START_TEST(test_addition_matrix_square)
{
    struct matrix matrix1 = {.row=2, .col=2};
    struct matrix matrix2 = {.row=2, .col=2};
    struct matrix matrix_res = {.data=NULL};
    
    int rc;

    matrix1.data = unit_allocate_matrix(matrix1.row, matrix1.col);
    matrix2.data = unit_allocate_matrix(matrix2.row, matrix2.col);

    double matrix1_in[][2] = {{1, 1}, {1, 1}};
    double matrix2_in[][2] = {{2, 2}, {2, 2}};
    double matrix_res_out[][2] = {{3, 3}, {3, 3}};

    for (size_t i = 0; i < matrix1.row; i++)
        for (size_t j = 0; j < matrix1.col; j++)
            matrix1.data[i][j] = matrix1_in[i][j];

    for (size_t i = 0; i < matrix2.row; i++)
        for (size_t j = 0; j < matrix2.col; j++)
            matrix2.data[i][j] = matrix2_in[i][j];

    rc = addition_matrix(&matrix1, &matrix2, &matrix_res);

    ck_assert_int_eq(rc, OK);

    for (size_t i = 0; i < matrix_res.row; i++)
        for (size_t j = 0; j < matrix_res.col; j++)
            ck_assert_double_eq(matrix_res_out[i][j], matrix_res.data[i][j]);

    free(matrix1.data);
    free(matrix2.data);
    free(matrix_res.data);
}
END_TEST

START_TEST(test_arithmetic_operations_null)
{
    int rc = arithmetic_operations(NULL, NULL, NULL, NULL);
    ck_assert_int_eq(rc, ERROR_EMPTY_PTR);
}
END_TEST

int unit_func_operation(const struct matrix *a, const struct matrix *b, struct matrix *res)
{
    return 2;
}

START_TEST(test_arithmetic_operations_empty_file_in1)
{
    int rc = arithmetic_operations("abc", "cda", "abc", unit_func_operation);
    ck_assert_int_eq(rc, ERROR_IO_FILE);
}
END_TEST

START_TEST(test_arithmetic_operations_error_file_in1)
{
    int rc;
    char input_file[L_tmpnam];
    char output_file[L_tmpnam];

    tmpnam(input_file);
    tmpnam(output_file);

    FILE *f = fopen(input_file, "w");
    fprintf(f, "abc acd\n");
    rewind(f);
    fclose(f);

    rc = arithmetic_operations(input_file, "bcd", "cda", unit_func_operation);
    ck_assert_int_eq(rc, ERROR_INVALID_SIZE);

    unlink(output_file);
    unlink(input_file);
}
END_TEST

START_TEST(test_arithmetic_operations_empty_file_in2)
{
    int rc;
    char input_file[L_tmpnam];
    char output_file[L_tmpnam];

    tmpnam(input_file);
    tmpnam(output_file);

    FILE *f = fopen(input_file, "w");
    fprintf(f, "1 1 4\n");
    rewind(f);
    fclose(f);

    rc = arithmetic_operations(input_file, "bcd", "cda", unit_func_operation);
    ck_assert_int_eq(rc, ERROR_IO_FILE);

    unlink(output_file);
    unlink(input_file);
}
END_TEST

START_TEST(test_arithmetic_operations_empty_error_file_in2)
{
    int rc;
    char input_file[L_tmpnam];
    char output_file[L_tmpnam];

    tmpnam(input_file);
    tmpnam(output_file);

    FILE *f = fopen(input_file, "w");
    fprintf(f, "1 1 4\n");
    rewind(f);
    fclose(f);

    FILE *f2 = fopen(output_file, "w");
    fprintf(f2, "abc as 4\n");
    rewind(f2);
    fclose(f2);

    rc = arithmetic_operations(input_file, output_file, "cda", unit_func_operation);
    ck_assert_int_eq(rc, ERROR_INVALID_SIZE);

    unlink(output_file);
    unlink(input_file);
}
END_TEST


START_TEST(test_arithmetic_operations_negative_func)
{
    int rc;
    char input_file[L_tmpnam];
    char output_file[L_tmpnam];
    char res_file[L_tmpnam];

    tmpnam(input_file);
    tmpnam(output_file);
    tmpnam(res_file);

    FILE *f = fopen(input_file, "w");
    fprintf(f, "1 1 4\n");
    rewind(f);
    fclose(f);

    FILE *f2 = fopen(output_file, "w");
    fprintf(f2, "1 1 5\n");
    rewind(f2);
    fclose(f2);

    rc = arithmetic_operations(input_file, output_file, res_file, unit_func_operation);
    ck_assert_int_eq(rc, 2);

    unlink(output_file);
    unlink(input_file);
    unlink(res_file);
}
END_TEST

Suite *addition_matrix_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("addition_matrix");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_addition_matrix_invalid_range);
    tcase_add_test(tc_neg, test_addition_matrix_NULL_res);
    tcase_add_test(tc_neg, test_ctrate_matrix_invalid_el_matrix);
    tcase_add_test(tc_neg, test_ctrate_matrix_negative_size);
    tcase_add_test(tc_neg, test_ctrate_matrix_str_size);
    tcase_add_test(tc_neg, test_ctrate_matrix_null);
    tcase_add_test(tc_neg, test_arithmetic_operations_null);
    tcase_add_test(tc_neg, test_arithmetic_operations_empty_file_in1);
    tcase_add_test(tc_neg, test_arithmetic_operations_error_file_in1);
    tcase_add_test(tc_neg, test_arithmetic_operations_empty_file_in2);
    tcase_add_test(tc_neg, test_arithmetic_operations_empty_error_file_in2);
    tcase_add_test(tc_neg, test_arithmetic_operations_negative_func);
    
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_addition_matrix_square);
    tcase_add_test(tc_pos, test_addition_matrix_single);
    tcase_add_test(tc_pos, test_addition_matrix_sum_zero_matrix);
    tcase_add_test(tc_pos, test_addition_matrix_reactangle);
    tcase_add_test(tc_pos, test_create_matrix);
  
    suite_add_tcase(s, tc_pos);

    return s;
}

START_TEST(test_multiply_matrix_NULL_res)
{

    struct matrix matrix1 = {.row=1, .col=1};
    struct matrix matrix2 = {.row=1, .col=1};

    matrix1.data = unit_allocate_matrix(matrix1.row, matrix1.col);
    matrix2.data = unit_allocate_matrix(matrix2.row, matrix2.col);

    int rc;

    rc = multiply_matrix(&matrix1, &matrix2, NULL);

    free(matrix1.data);
    free(matrix2.data);

    ck_assert_int_eq(rc, ERROR_EMPTY_PTR);
}
END_TEST

START_TEST(test_multiply_matrix_invalid_range)
{
    struct matrix matrix1 = {.row=1, .col=1};
    struct matrix matrix2 = {.row=2, .col=2};
    struct matrix matrix_res = {.data=NULL};

    matrix1.data = malloc(matrix1.row * sizeof(double*));
    matrix2.data = malloc(matrix2.row * sizeof(double*));

    int rc;

    rc = multiply_matrix(&matrix1, &matrix2, &matrix_res);

    free(matrix1.data);
    free(matrix2.data);
    free(matrix_res.data);

    ck_assert_int_eq(rc, ERROR_RANGE_MULT);
}
END_TEST

START_TEST(test_multiply_matrix_mul_singles_matrix)
{
    struct matrix matrix1 = {.row=2, .col=2};
    struct matrix matrix2 = {.row=2, .col=2};
    struct matrix matrix_res = {.data=NULL};
    
    int rc;

    matrix1.data = unit_allocate_matrix(matrix1.row, matrix1.col);
    matrix2.data = unit_allocate_matrix(matrix2.row, matrix2.col);

    double matrix1_in[][2] = {{5, 6}, {7, 8}};
    double matrix2_in[][2] = {{1, 0}, {0, 1}};
    double matrix_res_out[][2] = {{5, 6}, {7, 8}};

    for (size_t i = 0; i < matrix1.row; i++)
        for (size_t j = 0; j < matrix1.col; j++)
            matrix1.data[i][j] = matrix1_in[i][j];

    for (size_t i = 0; i < matrix2.row; i++)
        for (size_t j = 0; j < matrix2.col; j++)
            matrix2.data[i][j] = matrix2_in[i][j];

    rc = multiply_matrix(&matrix1, &matrix2, &matrix_res);

    ck_assert_int_eq(rc, OK);

    for (size_t i = 0; i < matrix_res.row; i++)
        for (size_t j = 0; j < matrix_res.col; j++)
            ck_assert_double_eq(matrix_res_out[i][j], matrix_res.data[i][j]);

    free(matrix1.data);
    free(matrix2.data);
    free(matrix_res.data);
}
END_TEST

START_TEST(test_multiply_matrix_reactangle)
{
    struct matrix matrix1 = {.row=2, .col=3};
    struct matrix matrix2 = {.row=3, .col=3};
    struct matrix matrix_res = {.data=NULL};
    
    int rc;

    matrix1.data = unit_allocate_matrix(matrix1.row, matrix1.col);
    matrix2.data = unit_allocate_matrix(matrix2.row, matrix2.col);

    double matrix1_in[][3] = {{1, 1, 1}, {1, 1, 1}};
    double matrix2_in[][3] = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
    double matrix_res_out[][3] = {{6, 6, 6}, {6, 6, 6}};

    for (size_t i = 0; i < matrix1.row; i++)
        for (size_t j = 0; j < matrix1.col; j++)
            matrix1.data[i][j] = matrix1_in[i][j];

    for (size_t i = 0; i < matrix2.row; i++)
        for (size_t j = 0; j < matrix2.col; j++)
            matrix2.data[i][j] = matrix2_in[i][j];

    rc = multiply_matrix(&matrix1, &matrix2, &matrix_res);

    ck_assert_int_eq(rc, OK);

    for (size_t i = 0; i < matrix_res.row; i++)
        for (size_t j = 0; j < matrix_res.col; j++)
            ck_assert_double_eq(matrix_res_out[i][j], matrix_res.data[i][j]);

    free(matrix1.data);
    free(matrix2.data);
    free(matrix_res.data);
}
END_TEST

START_TEST(test_multiply_matrix_single)
{
    struct matrix matrix1 = {.row=1, .col=1};
    struct matrix matrix2 = {.row=1, .col=1};
    struct matrix matrix_res = {.data=NULL};
    
    int rc;

    matrix1.data = unit_allocate_matrix(matrix1.row, matrix1.col);
    matrix2.data = unit_allocate_matrix(matrix2.row, matrix2.col);

    double matrix1_in[][1] = {{1}};
    double matrix2_in[][1] = {{2}};
    double matrix_res_out[][1] = {{2}};

    for (size_t i = 0; i < matrix1.row; i++)
        for (size_t j = 0; j < matrix1.col; j++)
            matrix1.data[i][j] = matrix1_in[i][j];

    for (size_t i = 0; i < matrix2.row; i++)
        for (size_t j = 0; j < matrix2.col; j++)
            matrix2.data[i][j] = matrix2_in[i][j];

    rc = multiply_matrix(&matrix1, &matrix2, &matrix_res);

    ck_assert_int_eq(rc, OK);

    for (size_t i = 0; i < matrix_res.row; i++)
        for (size_t j = 0; j < matrix_res.col; j++)
            ck_assert_double_eq(matrix_res_out[i][j], matrix_res.data[i][j]);

    free(matrix1.data);
    free(matrix2.data);
    free(matrix_res.data);
}
END_TEST

START_TEST(test_multiply_matrix_square)
{
    struct matrix matrix1 = {.row=2, .col=2};
    struct matrix matrix2 = {.row=2, .col=2};
    struct matrix matrix_res = {.data=NULL};
    
    int rc;

    matrix1.data = unit_allocate_matrix(matrix1.row, matrix1.col);
    matrix2.data = unit_allocate_matrix(matrix2.row, matrix2.col);

    double matrix1_in[][2] = {{1, 1}, {1, 1}};
    double matrix2_in[][2] = {{2, 2}, {2, 2}};
    double matrix_res_out[][2] = {{4, 4}, {4, 4}};

    for (size_t i = 0; i < matrix1.row; i++)
        for (size_t j = 0; j < matrix1.col; j++)
            matrix1.data[i][j] = matrix1_in[i][j];

    for (size_t i = 0; i < matrix2.row; i++)
        for (size_t j = 0; j < matrix2.col; j++)
            matrix2.data[i][j] = matrix2_in[i][j];

    rc = multiply_matrix(&matrix1, &matrix2, &matrix_res);

    ck_assert_int_eq(rc, OK);

    for (size_t i = 0; i < matrix_res.row; i++)
        for (size_t j = 0; j < matrix_res.col; j++)
            ck_assert_double_eq(matrix_res_out[i][j], matrix_res.data[i][j]);

    free(matrix1.data);
    free(matrix2.data);
    free(matrix_res.data);
}
END_TEST


Suite *multiply_matrix_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("multiply_matrix");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_multiply_matrix_NULL_res);
    tcase_add_test(tc_neg, test_multiply_matrix_invalid_range);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_multiply_matrix_mul_singles_matrix);
    tcase_add_test(tc_pos, test_multiply_matrix_reactangle);
    tcase_add_test(tc_pos, test_multiply_matrix_single);
    tcase_add_test(tc_pos, test_multiply_matrix_square);
  
    suite_add_tcase(s, tc_pos);

    return s;
}

START_TEST(test_solution_gauss_NULL)
{
    int rc;

    rc = solution_gaus(NULL, NULL, NULL);

    ck_assert_int_eq(rc, ERROR_EMPTY_PTR);
}
END_TEST

START_TEST(test_solution_gauss_row_matrix_NULL_ptr)
{
    int rc;

    rc = solution_gauss_row(NULL, NULL);

    ck_assert_int_eq(rc, ERROR_EMPTY_PTR);
}
END_TEST

START_TEST(test_solution_gauss_row_matrix_empty_file)
{
    int rc;
    char input_file[L_tmpnam];
    char output_file[L_tmpnam];

    tmpnam(input_file);
    tmpnam(output_file);

    FILE *f = fopen(output_file, "r");
    if (f)
        fclose(f);

    rc = solution_gauss_row(input_file, output_file);
    ck_assert_int_eq(rc, ERROR_IO_FILE);

    unlink(output_file);
}
END_TEST

START_TEST(test_solution_gauss_row_matrix_empty_vector)
{
    int rc;
    char input_file[L_tmpnam];
    char output_file[L_tmpnam];

    tmpnam(input_file);
    tmpnam(output_file);

    FILE *f = fopen(input_file, "w");
    if (f)
        fclose(f);

    rc = solution_gauss_row(input_file, output_file);
    ck_assert_int_eq(rc, ERROR_INVALID_SIZE);

    unlink(input_file);
    unlink(output_file);
}
END_TEST

START_TEST(test_solution_gauss_row_matrix_rectangle)
{
    int rc;
    char input_file[L_tmpnam];
    char output_file[L_tmpnam];

    tmpnam(input_file);
    tmpnam(output_file);

    FILE *f_in = fopen(input_file, "w");
    
    if (f_in)
    {
        fprintf(f_in, "%d %d\n", 3, 5);
        fprintf(f_in, "%d %d %d %d %d\n", 1, 2, 3, 4, 4);
        fprintf(f_in, "%d %d %d %d %d\n", 5, 6, 7, 8, 4);
        fprintf(f_in, "%d %d %d %d %d\n", 9, 1, 1, 2, 4);
    }
    
    if (f_in) fclose(f_in);

    rc = solution_gauss_row(input_file, output_file);
    ck_assert_int_eq(rc, ERROR_RANGE_GAUS);

    unlink(input_file);
    unlink(output_file);
}
END_TEST

START_TEST(test_solution_gauss_row_matrix_correct)
{
    int rc;
    char input_file[L_tmpnam];
    char output_file[L_tmpnam];
    char expected_file[L_tmpnam];

    tmpnam(input_file);
    tmpnam(output_file);
    tmpnam(expected_file);

    FILE *f_in = fopen(input_file, "w");
    
    if (f_in)
    {
        fprintf(f_in, "%d %d\n", 2, 3);
        fprintf(f_in, "%d %d %d\n", 1, 1, 2);
        fprintf(f_in, "%d %d %d\n", 1, 0, 4);
    }
    
    if (f_in) fclose(f_in);

    FILE *f_exp = fopen(expected_file, "w");
    
    if (f_exp)
    {
        fprintf(f_exp, "%d %d\n", 2, 1);
        fprintf(f_exp, "%d\n", 4);
        fprintf(f_exp, "%d\n", -2);
    }
    
    if (f_exp) fclose(f_exp);

    rc = solution_gauss_row(input_file, output_file);
    ck_assert_int_eq(rc, OK);

    FILE *f1 = fopen(output_file, "r");
    FILE *f2 = fopen(expected_file, "r");
    double el1, el2;

    if (f1 && f2)
    {
        while (fscanf(f1, "%lf", &el1) == 1 && fscanf(f2, "%lf", &el2) == 1)
            ck_assert_double_eq_tol(el1, el2, 1e-6);
    }

    if (f1) fclose(f1);
    if (f2) fclose(f2);

    unlink(input_file);
    unlink(output_file);
    unlink(expected_file);
}
END_TEST

START_TEST(test_solution_gauss_row_matrix_single_matr)
{
    int rc;
    char input_file[L_tmpnam];
    char output_file[L_tmpnam];
    char expected_file[L_tmpnam];

    tmpnam(input_file);
    tmpnam(output_file);
    tmpnam(expected_file);

    FILE *f_in = fopen(input_file, "w");
    
    if (f_in)
    {
        fprintf(f_in, "%d %d\n", 1, 2);
        fprintf(f_in, "%d %d\n", 2, 2);
    }
    
    if (f_in) fclose(f_in);

    FILE *f_exp = fopen(expected_file, "w");
    
    if (f_exp)
    {
        fprintf(f_exp, "%d %d\n", 1, 1);
        fprintf(f_exp, "%d\n", 1);
    }
    
    if (f_exp) fclose(f_exp);

    rc = solution_gauss_row(input_file, output_file);
    ck_assert_int_eq(rc, OK);

    FILE *f1 = fopen(output_file, "r");
    FILE *f2 = fopen(expected_file, "r");
    double el1, el2;

    if (f1 && f2)
    {
        while (fscanf(f1, "%lf", &el1) == 1 && fscanf(f2, "%lf", &el2) == 1)
            ck_assert_double_eq_tol(el1, el2, 1e-6);
    }

    if (f1) fclose(f1);
    if (f2) fclose(f2);

    unlink(input_file);
    unlink(output_file);
    unlink(expected_file);
}
END_TEST

START_TEST(test_solution_gauss_row_matrix_degenerate)
{
    int rc;
    char input_file[L_tmpnam];
    char output_file[L_tmpnam];
    char expected_file[L_tmpnam];

    tmpnam(input_file);
    tmpnam(output_file);
    tmpnam(expected_file);

    FILE *f_in = fopen(input_file, "w");
    
    if (f_in)
    {
        fprintf(f_in, "%d %d\n", 2, 3);
        fprintf(f_in, "%d %d %d\n", 2, 2, 2);
        fprintf(f_in, "%d %d %d\n", 1, 1, 1);
    }
    
    if (f_in) fclose(f_in);

    FILE *f_exp = fopen(expected_file, "w");
    
    if (f_exp) fclose(f_exp);

    rc = solution_gauss_row(input_file, output_file);
    ck_assert_int_eq(rc, ERROR_DEGENERATE_MATRIX);

    unlink(input_file);
    unlink(output_file);
    unlink(expected_file);
}
END_TEST

START_TEST(test_ctrate_matrix_expand_null)
{
    FILE *f = tmpfile();
    double *vector = NULL;

    int rc = create_matrix_expand(f, NULL, &vector);

    ck_assert_int_eq(rc, ERROR_EMPTY_PTR);
}
END_TEST

START_TEST(test_ctrate_matrix_expand_str_size)
{
    FILE *f = tmpfile();
    fprintf(f, "abc cda\n");
    rewind(f);
    double *vector = NULL;
    struct matrix matrix = { .data=NULL, .row=0, .col=0, .ptr_free=NULL };

    int rc = create_matrix_expand(f, &matrix, &vector);

    ck_assert_int_eq(rc, ERROR_INVALID_SIZE);
}
END_TEST

START_TEST(test_ctrate_matrix_expand_negative_size)
{
    FILE *f = tmpfile();
    fprintf(f, "%d %d\n", -12, 0);
    rewind(f);
    double *vector = NULL;
    struct matrix matrix = { .data=NULL, .row=0, .col=0, .ptr_free=NULL };

    int rc = create_matrix_expand(f, &matrix, &vector);

    free(matrix.ptr_free);
    ck_assert_int_eq(rc, ERROR_INVALID_RANGE);
}
END_TEST

START_TEST(test_ctrate_matrix_expand_invalid_gaus_range)
{
    FILE *f = tmpfile();
    fprintf(f, "5 2\n");
    rewind(f);
    double *vector = NULL;
    struct matrix matrix = { .data=NULL, .row=0, .col=0, .ptr_free=NULL };

    int rc = create_matrix_expand(f, &matrix, &vector);

    ck_assert_int_eq(rc, ERROR_RANGE_GAUS);
}
END_TEST

START_TEST(test_ctrate_matrix_expand_invalid_el_matrix)
{
    FILE *f = tmpfile();
    fprintf(f, "2 3 3 4 2 abc 2 3\n");
    rewind(f);
    double *vector = NULL;
    struct matrix matrix = { .data=NULL, .row=0, .col=0, .ptr_free=NULL };

    int rc = create_matrix_expand(f, &matrix, &vector);
    
    ck_assert_int_eq(rc, ERRROR_INVALID_EL);
}
END_TEST

START_TEST(test_ctrate_matrix_expand_invalid_el_vector)
{
    FILE *f = tmpfile();
    fprintf(f, "2 3 3 4 abc 3 3 3\n");
    rewind(f);
    double *vector = NULL;
    struct matrix matrix = { .data=NULL, .row=0, .col=0, .ptr_free=NULL };

    int rc = create_matrix_expand(f, &matrix, &vector);

    ck_assert_int_eq(rc, ERROR_INVALID_EL_VECTOR);
}
END_TEST

START_TEST(test_search_max_row)
{
    double arr[] = {1, 2, 3, 4, 5};

    size_t index = search_max_row(arr, 5, 0);

    ck_assert_int_eq(index, 4);
}
END_TEST

START_TEST(test_swap)
{
    char a = 'a';
    char b = 'b';

    swap(&a, &b, sizeof(a));

    ck_assert_int_eq(a, 'b');
    ck_assert_int_eq(b, 'a');
}
END_TEST

Suite *solution_gauss_row_matrix_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("solution_gauss_row");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_solution_gauss_row_matrix_NULL_ptr);
    tcase_add_test(tc_neg, test_solution_gauss_row_matrix_empty_file);
    tcase_add_test(tc_neg, test_solution_gauss_row_matrix_empty_vector);
    tcase_add_test(tc_neg, test_solution_gauss_row_matrix_rectangle);
    tcase_add_test(tc_neg, test_solution_gauss_row_matrix_degenerate);
    tcase_add_test(tc_neg, test_solution_gauss_NULL);
    tcase_add_test(tc_neg, test_ctrate_matrix_expand_invalid_gaus_range);
    tcase_add_test(tc_neg, test_ctrate_matrix_expand_invalid_el_matrix);
    tcase_add_test(tc_neg, test_ctrate_matrix_expand_invalid_el_vector);
    tcase_add_test(tc_neg, test_ctrate_matrix_expand_negative_size);
    tcase_add_test(tc_neg, test_ctrate_matrix_expand_str_size);
    tcase_add_test(tc_neg, test_ctrate_matrix_expand_null);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_solution_gauss_row_matrix_correct);
    tcase_add_test(tc_pos, test_solution_gauss_row_matrix_single_matr);
    tcase_add_test(tc_pos, test_search_max_row);
    tcase_add_test(tc_pos, test_swap);
  
    suite_add_tcase(s, tc_pos);

    return s;
}

; ModuleID = 'demo'
source_filename = "demo"
target triple = "arm64-apple-darwin22.1.0"

@vtable_Object = internal constant [2 x ptr] [ptr @id_Object, ptr @vtable_Object]
@id_Object = internal constant i32 0

declare ptr @calloc(i32, i32)

declare void @output(i32)

define i32 @main() {
entry:
  %0 = alloca ptr, align 8
  %calloced = call ptr @calloc(i32 1, i32 320)
  store ptr %calloced, ptr %0, align 8
  %1 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  br label %header

header:                                           ; preds = %exit6, %entry
  %var = load i32, ptr %1, align 4
  %2 = icmp slt i32 %var, 5
  br i1 %2, label %body, label %exit

body:                                             ; preds = %header
  %calloced1 = call ptr @calloc(i32 1, i32 24)
  %var2 = load ptr, ptr %0, align 8
  %var3 = load i32, ptr %1, align 4
  %3 = getelementptr [0 x ptr], ptr %var2, i32 0, i32 %var3
  store ptr %calloced1, ptr %3, align 8
  %4 = alloca i32, align 4
  store i32 0, ptr %4, align 4
  br label %header4

exit:                                             ; preds = %header
  store i32 0, ptr %1, align 4
  br label %header17

header4:                                          ; preds = %body5, %body
  %var7 = load i32, ptr %4, align 4
  %5 = icmp slt i32 %var7, 6
  br i1 %5, label %body5, label %exit6

body5:                                            ; preds = %header4
  %var8 = load i32, ptr %1, align 4
  %var9 = load i32, ptr %4, align 4
  %mul_tmp = mul i32 %var8, %var9
  %var10 = load ptr, ptr %0, align 8
  %var11 = load i32, ptr %1, align 4
  %6 = getelementptr [0 x ptr], ptr %var10, i32 0, i32 %var11
  %var12 = load ptr, ptr %6, align 8
  %var13 = load i32, ptr %4, align 4
  %7 = getelementptr [0 x i32], ptr %var12, i32 0, i32 %var13
  store i32 %mul_tmp, ptr %7, align 4
  %var14 = load i32, ptr %4, align 4
  %add_tmp = add i32 %var14, 1
  store i32 %add_tmp, ptr %4, align 4
  br label %header4

exit6:                                            ; preds = %header4
  %var15 = load i32, ptr %1, align 4
  %add_tmp16 = add i32 %var15, 1
  store i32 %add_tmp16, ptr %1, align 4
  br label %header

header17:                                         ; preds = %exit23, %exit
  %var20 = load i32, ptr %1, align 4
  %8 = icmp slt i32 %var20, 5
  br i1 %8, label %body18, label %exit19

body18:                                           ; preds = %header17
  %9 = alloca i32, align 4
  store i32 0, ptr %9, align 4
  br label %header21

exit19:                                           ; preds = %header17
  ret i32 0

header21:                                         ; preds = %body22, %body18
  %var24 = load i32, ptr %9, align 4
  %10 = icmp slt i32 %var24, 6
  br i1 %10, label %body22, label %exit23

body22:                                           ; preds = %header21
  %var25 = load ptr, ptr %0, align 8
  %var26 = load i32, ptr %1, align 4
  %11 = getelementptr [0 x ptr], ptr %var25, i32 0, i32 %var26
  %var27 = load ptr, ptr %11, align 8
  %var28 = load i32, ptr %9, align 4
  %12 = getelementptr [0 x i32], ptr %var27, i32 0, i32 %var28
  %var29 = load i32, ptr %12, align 4
  call void @output(i32 %var29)
  %var30 = load i32, ptr %9, align 4
  %add_tmp31 = add i32 %var30, 1
  store i32 %add_tmp31, ptr %9, align 4
  br label %header21

exit23:                                           ; preds = %header21
  %var32 = load i32, ptr %1, align 4
  %add_tmp33 = add i32 %var32, 1
  store i32 %add_tmp33, ptr %1, align 4
  br label %header17
}

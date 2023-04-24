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
  %1 = alloca ptr, align 8
  store i32 0, ptr %0, align 4
  store i32 0, ptr %1, align 4
  br label %header

header:                                           ; preds = %body, %entry
  %var = load i32, ptr %0, align 4
  %2 = icmp slt i32 %var, 10
  br i1 %2, label %body, label %exit

body:                                             ; preds = %header
  %var1 = load i32, ptr %0, align 4
  %add_tmp = add i32 %var1, 1
  store i32 %add_tmp, ptr %0, align 4
  %var2 = load i32, ptr %1, align 4
  %var3 = load i32, ptr %0, align 4
  %add_tmp4 = add i32 %var2, %var3
  store i32 %add_tmp4, ptr %1, align 4
  br label %header

exit:                                             ; preds = %header
  %var5 = load i32, ptr %1, align 4
  call void @output(i32 %var5)
  ret i32 0
}

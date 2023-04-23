; ModuleID = 'demo'
source_filename = "demo"
target triple = "arm64-apple-darwin22.1.0"

%struct_Person = type <{ ptr, i32 }>
%struct_Employee = type <{ ptr, i32, i32 }>
%struct_Admin = type <{ ptr, i32, i32, i32 }>

@vtable_Object = internal constant [2 x ptr] [ptr @id_Object, ptr @vtable_Object]
@vtable_Person = internal constant [5 x ptr] [ptr @id_Person, ptr @vtable_Object, ptr @Person_init_Int, ptr @Person_getId, ptr @Person_speak]
@vtable_Admin = internal constant [5 x ptr] [ptr @id_Admin, ptr @vtable_Employee, ptr @Admin_init_Int_Int_Int, ptr @Admin_getId, ptr @Admin_speak]
@vtable_Employee = internal constant [5 x ptr] [ptr @id_Employee, ptr @vtable_Person, ptr @Employee_init_Int_Int, ptr @Person_getId, ptr @Employee_speak]
@id_Object = internal constant i32 0
@id_Person = internal constant i32 1
@id_Admin = internal constant i32 2
@id_Employee = internal constant i32 3

declare ptr @calloc(i32, i32)

declare void @output(i32)

define void @Program_speak_Person(ptr %0) {
entry:
  %1 = alloca ptr, align 8
  store ptr %0, ptr %1, align 8
  %var = load ptr, ptr %1, align 8
  %2 = getelementptr inbounds %struct_Person, ptr %var, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  %4 = getelementptr [5 x ptr], ptr %3, i32 0, i32 3
  %5 = load ptr, ptr %4, align 8
  %6 = call i32 %5(ptr %var)
  call void @output(i32 %6)
  %var1 = load ptr, ptr %1, align 8
  %7 = getelementptr inbounds %struct_Person, ptr %var1, i32 0, i32 0
  %8 = load ptr, ptr %7, align 8
  %9 = getelementptr [5 x ptr], ptr %8, i32 0, i32 4
  %10 = load ptr, ptr %9, align 8
  call void %10(ptr %var1)
  ret void
}

define i32 @main() {
entry:
  %0 = alloca ptr, align 8
  %1 = alloca ptr, align 8
  %2 = alloca ptr, align 8
  %calloced = call ptr @calloc(i32 1, i32 12)
  %3 = getelementptr inbounds %struct_Person, ptr %calloced, i32 0, i32 0
  store ptr @vtable_Person, ptr %3, align 8
  %4 = load ptr, ptr getelementptr inbounds ([5 x ptr], ptr @vtable_Person, i32 0, i32 2), align 8
  call void %4(ptr %calloced, i32 1)
  store ptr %calloced, ptr %0, align 8
  %calloced1 = call ptr @calloc(i32 1, i32 16)
  %5 = getelementptr inbounds %struct_Employee, ptr %calloced1, i32 0, i32 0
  store ptr @vtable_Employee, ptr %5, align 8
  %6 = load ptr, ptr getelementptr inbounds ([5 x ptr], ptr @vtable_Employee, i32 0, i32 2), align 8
  call void %6(ptr %calloced1, i32 2, i32 100)
  store ptr %calloced1, ptr %1, align 8
  %calloced2 = call ptr @calloc(i32 1, i32 20)
  %7 = getelementptr inbounds %struct_Admin, ptr %calloced2, i32 0, i32 0
  store ptr @vtable_Admin, ptr %7, align 8
  %8 = load ptr, ptr getelementptr inbounds ([5 x ptr], ptr @vtable_Admin, i32 0, i32 2), align 8
  call void %8(ptr %calloced2, i32 3, i32 1000, i32 5)
  store ptr %calloced2, ptr %2, align 8
  %var = load ptr, ptr %0, align 8
  call void @Program_speak_Person(ptr %var)
  %var3 = load ptr, ptr %1, align 8
  call void @Program_speak_Person(ptr %var3)
  %var4 = load ptr, ptr %2, align 8
  call void @Program_speak_Person(ptr %var4)
  ret i32 0
}

define void @Person_init_Int(ptr %0, i32 %1) {
entry:
  %2 = alloca ptr, align 8
  store i32 %1, ptr %2, align 4
  %var = load i32, ptr %2, align 4
  %3 = getelementptr inbounds %struct_Person, ptr %0, i32 0, i32 1
  store i32 %var, ptr %3, align 4
  %var1 = load i32, ptr %2, align 4
  call void @output(i32 %var1)
  ret void
}

define i32 @Person_getId(ptr %0) {
entry:
  %1 = getelementptr inbounds %struct_Person, ptr %0, i32 0, i32 1
  %var = load i32, ptr %1, align 4
  ret i32 %var
}

define void @Person_speak(ptr %0) {
entry:
  call void @output(i32 99)
  ret void
}

define void @Admin_init_Int_Int_Int(ptr %0, i32 %1, i32 %2, i32 %3) {
entry:
  %4 = alloca ptr, align 8
  store i32 %1, ptr %4, align 4
  %5 = alloca ptr, align 8
  store i32 %2, ptr %5, align 4
  %6 = alloca ptr, align 8
  store i32 %3, ptr %6, align 4
  %var = load i32, ptr %4, align 4
  %var1 = load i32, ptr %5, align 4
  %7 = load ptr, ptr getelementptr inbounds ([5 x ptr], ptr @vtable_Employee, i32 0, i32 2), align 8
  call void %7(ptr %0, i32 %var, i32 %var1)
  %var2 = load i32, ptr %6, align 4
  %8 = getelementptr inbounds %struct_Admin, ptr %0, i32 0, i32 3
  store i32 %var2, ptr %8, align 4
  %var3 = load i32, ptr %6, align 4
  call void @output(i32 %var3)
  ret void
}

define i32 @Admin_getId(ptr %0) {
entry:
  call void @output(i32 105)
  %1 = getelementptr inbounds %struct_Admin, ptr %0, i32 0, i32 1
  %var = load i32, ptr %1, align 4
  ret i32 %var
}

define void @Admin_speak(ptr %0) {
entry:
  %1 = load ptr, ptr getelementptr inbounds ([5 x ptr], ptr @vtable_Employee, i32 0, i32 4), align 8
  call void %1(ptr %0)
  call void @output(i32 103)
  ret void
}

define void @Employee_init_Int_Int(ptr %0, i32 %1, i32 %2) {
entry:
  %3 = alloca ptr, align 8
  store i32 %1, ptr %3, align 4
  %4 = alloca ptr, align 8
  store i32 %2, ptr %4, align 4
  %var = load i32, ptr %3, align 4
  %5 = load ptr, ptr getelementptr inbounds ([5 x ptr], ptr @vtable_Person, i32 0, i32 2), align 8
  call void %5(ptr %0, i32 %var)
  %var1 = load i32, ptr %4, align 4
  %6 = getelementptr inbounds %struct_Employee, ptr %0, i32 0, i32 2
  store i32 %var1, ptr %6, align 4
  %var2 = load i32, ptr %4, align 4
  call void @output(i32 %var2)
  ret void
}

define void @Employee_speak(ptr %0) {
entry:
  %1 = load ptr, ptr getelementptr inbounds ([5 x ptr], ptr @vtable_Person, i32 0, i32 4), align 8
  call void %1(ptr %0)
  call void @output(i32 101)
  ret void
}

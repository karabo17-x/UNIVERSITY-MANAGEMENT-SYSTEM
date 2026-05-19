CXX = g++
MOC = moc
CXXFLAGS = -std=c++17 -Wall -Wextra -fPIC
QT_PATH = /usr/include/x86_64-linux-gnu/qt6
QT_FLAGS = -I$(QT_PATH) -I$(QT_PATH)/QtCore -I$(QT_PATH)/QtGui -I$(QT_PATH)/QtWidgets -I/usr/lib/x86_64-linux-gnu/qt6/mkspecs/linux-g++ -fPIC
QT_LIBS = -lQt6Core -lQt6Gui -lQt6Widgets
CXXFLAGS += $(QT_FLAGS)
TARGET = university_system

# Source and object files with their directories
PERSON_SRC = Person/Person.cpp
STUDENT_SRC = Student/Student.cpp
FACULTY_SRC = Faculty/Faculty.cpp
DEPARTMENT_SRC = Department/Department.cpp
ADMINISTRATION_SRC = Administration/Administration.cpp
ACADEMIC_SRC = Academic/AcademicAdmin.cpp
RESIDENCE_SRC = Residence/Residence.cpp
SPORTS_SRC = Sports/Sports.cpp
SPORTS_AFFILIATION_SRC = Sports/SportsAffiliation.cpp
EXAM_SRC = Exam/Exam.cpp
EXAM_SECTION_SRC = Exam/ExamSection.cpp
EXAM_SCHEDULE_SRC = Exam/ExamSchedule.cpp
MAIN_SRC = Main/main.cpp
MAINWINDOW_SRC = Main/MainWindow.cpp
STUDENT_DIALOG_SRC = Main/StudentRegistrationDialog.cpp
STUDENT_SEARCH_SRC = Main/StudentSearchDialog.cpp
GENERIC_LIST_SRC = Main/GenericListDialog.cpp
MAINWINDOW_HEADER = Main/MainWindow.h
MAINWINDOW_MOC_SRC = Main/moc_MainWindow.cpp

PERSON_OBJ = Person/Person.o
STUDENT_OBJ = Student/Student.o
FACULTY_OBJ = Faculty/Faculty.o
DEPARTMENT_OBJ = Department/Department.o
ADMINISTRATION_OBJ = Administration/Administration.o
ACADEMIC_OBJ = Academic/AcademicAdmin.o
RESIDENCE_OBJ = Residence/Residence.o
SPORTS_OBJ = Sports/Sports.o
SPORTS_AFFILIATION_OBJ = Sports/SportsAffiliation.o
EXAM_OBJ = Exam/Exam.o
EXAM_SECTION_OBJ = Exam/ExamSection.o
EXAM_SCHEDULE_OBJ = Exam/ExamSchedule.o
MAIN_OBJ = Main/main.o
MAINWINDOW_OBJ = Main/MainWindow.o
STUDENT_DIALOG_OBJ = Main/StudentRegistrationDialog.o
STUDENT_SEARCH_OBJ = Main/StudentSearchDialog.o
GENERIC_LIST_OBJ = Main/GenericListDialog.o
MAINWINDOW_MOC_OBJ = Main/moc_MainWindow.o

OBJECTS = $(PERSON_OBJ) $(STUDENT_OBJ) $(FACULTY_OBJ) $(DEPARTMENT_OBJ) $(ADMINISTRATION_OBJ) $(ACADEMIC_OBJ) $(RESIDENCE_OBJ) $(SPORTS_OBJ) $(SPORTS_AFFILIATION_OBJ) $(EXAM_OBJ) $(EXAM_SECTION_OBJ) $(EXAM_SCHEDULE_OBJ) $(MAIN_OBJ) $(MAINWINDOW_OBJ) $(STUDENT_DIALOG_OBJ) $(STUDENT_SEARCH_OBJ) $(GENERIC_LIST_OBJ) $(MAINWINDOW_MOC_OBJ)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(QT_LIBS)
	@echo "Build successful! Executable: $(TARGET)"

# Qt Meta-Object Compiler
Main/moc_MainWindow.cpp: Main/MainWindow.h
	$(MOC) $(QT_FLAGS) Main/MainWindow.h -o Main/moc_MainWindow.cpp
	@echo "Generated moc file for MainWindow.h"

# Compile moc-generated source files to object files
Main/moc_MainWindow.o: Main/moc_MainWindow.cpp
	$(CXX) $(CXXFLAGS) -c Main/moc_MainWindow.cpp -o Main/moc_MainWindow.o
	@echo "Compiled moc_MainWindow.cpp"

# Compile source files to object files
Person/Person.o: Person/Person.cpp Person/Person.h
	$(CXX) $(CXXFLAGS) -c Person/Person.cpp -o Person/Person.o
	@echo "Compiled Person/Person.cpp"

Student/Student.o: Student/Student.cpp Student/Student.h Person/Person.h
	$(CXX) $(CXXFLAGS) -c Student/Student.cpp -o Student/Student.o
	@echo "Compiled Student/Student.cpp"

Faculty/Faculty.o: Faculty/Faculty.cpp Faculty/Faculty.h Person/Person.h
	$(CXX) $(CXXFLAGS) -c Faculty/Faculty.cpp -o Faculty/Faculty.o
	@echo "Compiled Faculty/Faculty.cpp"

Department/Department.o: Department/Department.cpp Department/Department.h
	$(CXX) $(CXXFLAGS) -c Department/Department.cpp -o Department/Department.o
	@echo "Compiled Department/Department.cpp"

Administration/Administration.o: Administration/Administration.cpp Administration/Administration.h Student/Student.h
	$(CXX) $(CXXFLAGS) -c Administration/Administration.cpp -o Administration/Administration.o
	@echo "Compiled Administration/Administration.cpp"

Academic/AcademicAdmin.o: Academic/AcademicAdmin.cpp Academic/AcademicAdmin.h Student/Student.h
	$(CXX) $(CXXFLAGS) -c Academic/AcademicAdmin.cpp -o Academic/AcademicAdmin.o
	@echo "Compiled Academic/AcademicAdmin.cpp"

Residence/Residence.o: Residence/Residence.cpp Residence/Residence.h Student/Student.h
	$(CXX) $(CXXFLAGS) -c Residence/Residence.cpp -o Residence/Residence.o
	@echo "Compiled Residence/Residence.cpp"

Sports/Sports.o: Sports/Sports.cpp Sports/Sports.h
	$(CXX) $(CXXFLAGS) -c Sports/Sports.cpp -o Sports/Sports.o
	@echo "Compiled Sports/Sports.cpp"

Sports/SportsAffiliation.o: Sports/SportsAffiliation.cpp Sports/SportsAffiliation.h Sports/Sports.h
	$(CXX) $(CXXFLAGS) -c Sports/SportsAffiliation.cpp -o Sports/SportsAffiliation.o
	@echo "Compiled Sports/SportsAffiliation.cpp"

Exam/Exam.o: Exam/Exam.cpp Exam/Exam.h
	$(CXX) $(CXXFLAGS) -c Exam/Exam.cpp -o Exam/Exam.o
	@echo "Compiled Exam/Exam.cpp"

Exam/ExamSection.o: Exam/ExamSection.cpp Exam/ExamSection.h Exam/Exam.h
	$(CXX) $(CXXFLAGS) -c Exam/ExamSection.cpp -o Exam/ExamSection.o
	@echo "Compiled Exam/ExamSection.cpp"

Exam/ExamSchedule.o: Exam/ExamSchedule.cpp Exam/ExamSchedule.h Exam/ExamSection.h
	$(CXX) $(CXXFLAGS) -c Exam/ExamSchedule.cpp -o Exam/ExamSchedule.o
	@echo "Compiled Exam/ExamSchedule.cpp"

Main/main.o: Main/main.cpp Main/MainWindow.h
	$(CXX) $(CXXFLAGS) -c Main/main.cpp -o Main/main.o
	@echo "Compiled Main/main.cpp"

Main/MainWindow.o: Main/MainWindow.cpp Main/MainWindow.h Person/Person.h Student/Student.h Faculty/Faculty.h Department/Department.h Administration/Administration.h Academic/AcademicAdmin.h Residence/Residence.h Sports/Sports.h Sports/SportsAffiliation.h Exam/Exam.h Exam/ExamSection.h Exam/ExamSchedule.h
	$(CXX) $(CXXFLAGS) -c Main/MainWindow.cpp -o Main/MainWindow.o
	@echo "Compiled Main/MainWindow.cpp"

Main/StudentRegistrationDialog.o: Main/StudentRegistrationDialog.cpp Main/StudentRegistrationDialog.h Main/MainWindow.h
	$(CXX) $(CXXFLAGS) -c Main/StudentRegistrationDialog.cpp -o Main/StudentRegistrationDialog.o
	@echo "Compiled Main/StudentRegistrationDialog.cpp"

Main/StudentSearchDialog.o: Main/StudentSearchDialog.cpp Main/StudentSearchDialog.h Main/MainWindow.h
	$(CXX) $(CXXFLAGS) -c Main/StudentSearchDialog.cpp -o Main/StudentSearchDialog.o
	@echo "Compiled Main/StudentSearchDialog.cpp"

Main/GenericListDialog.o: Main/GenericListDialog.cpp Main/GenericListDialog.h
	$(CXX) $(CXXFLAGS) -c Main/GenericListDialog.cpp -o Main/GenericListDialog.o
	@echo "Compiled Main/GenericListDialog.cpp"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean object files and executable
clean:
	rm -f $(OBJECTS) $(TARGET) Main/moc_MainWindow.cpp
	@echo "Clean successful!"

# Help message
help:
	@echo "Available targets:"
	@echo "  make       - Build the program"
	@echo "  make run   - Build and run the program"
	@echo "  make clean - Remove compiled files"
	@echo "  make help  - Show this help message"

.PHONY: all run clean help

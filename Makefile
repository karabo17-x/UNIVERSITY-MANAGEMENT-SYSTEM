CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = university_system

# Source and object files with their directories
PERSON_SRC = Person/Person.cpp
STUDENT_SRC = Student/Student.cpp
FACULTY_SRC = Faculty/Faculty.cpp
DEPARTMENT_SRC = Department/Department.cpp
ADMINISTRATION_SRC = Administration/Administration.cpp
ACADEMIC_SRC = Academic/AcademicAdmin.cpp
RESIDENCE_SRC = Residence/Residence.cpp
MAIN_SRC = Main/main.cpp

PERSON_OBJ = Person/Person.o
STUDENT_OBJ = Student/Student.o
FACULTY_OBJ = Faculty/Faculty.o
DEPARTMENT_OBJ = Department/Department.o
ADMINISTRATION_OBJ = Administration/Administration.o
ACADEMIC_OBJ = Academic/AcademicAdmin.o
RESIDENCE_OBJ = Residence/Residence.o
MAIN_OBJ = Main/main.o

OBJECTS = $(PERSON_OBJ) $(STUDENT_OBJ) $(FACULTY_OBJ) $(DEPARTMENT_OBJ) $(ADMINISTRATION_OBJ) $(ACADEMIC_OBJ) $(RESIDENCE_OBJ) $(MAIN_OBJ)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build successful! Executable: $(TARGET)"

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

Main/main.o: Main/main.cpp Person/Person.h Student/Student.h Faculty/Faculty.h Department/Department.h Administration/Administration.h Academic/AcademicAdmin.h Residence/Residence.h
	$(CXX) $(CXXFLAGS) -c Main/main.cpp -o Main/main.o
	@echo "Compiled Main/main.cpp"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean object files and executable
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean successful!"

# Help message
help:
	@echo "Available targets:"
	@echo "  make       - Build the program"
	@echo "  make run   - Build and run the program"
	@echo "  make clean - Remove compiled files"
	@echo "  make help  - Show this help message"

.PHONY: all run clean help

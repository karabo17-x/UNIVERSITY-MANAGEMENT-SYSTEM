# EXAM SECTIONS FEATURE - USAGE GUIDE

## Overview
This document provides comprehensive instructions on using the Exam Sections feature in the University Management System.

## Feature Summary
The exam sections feature allows administrators to:
- Create exam schedules for each department per semester
- Define exam sections with specific invigilators and capacity limits
- Add various types of exams (Midterm, Final, Quiz, Assignment) to sections
- Enroll students in specific exam sections
- View exam schedules and enrolled student lists

## Getting Started

### Step 1: Start the Application
```bash
./university_system
```

### Step 2: Initialize Department Exam Schedule
**Menu Option: 22**

1. Select a department from the 8 available:
   - Computer Science
   - Electronics
   - Mathematics
   - Physics
   - Statistics
   - Engineering
   - Information Technology
   - Cybersecurity

2. Enter the semester 

3. The system creates an exam schedule for that department

### Step 3: Create Exam Sections
**Menu Option: 23**

1. Select the department
2. Enter section details:
   - **Section ID**: Unique identifier (e.g., "SEC001")
   - **Section Name**: Descriptive name (e.g., "CS101 Section A")
   - **Invigilator Name**: Faculty overseeing the exam (e.g., "Dr. Reabetswe Kimberely")
   - **Room Number**: Physical location (e.g., "Room 101", "Lab A")
   - **Capacity**: Maximum students allowed (e.g., 30, 50)

### Step 4: Add Exams to Sections
**Menu Option: 24**

1. Select the department
2. Enter the section ID where you want to add the exam
3. Enter exam details:
   - **Exam ID**: Unique identifier (e.g., "MID001")
   - **Exam Name**: Subject/course name (e.g., "Programming Fundamentals")
   - **Exam Type**: Choose from:
     - Midterm
     - Final
     - Quiz
     - Assignment
   - **Date**: In DD/MM/YYYY format (e.g., "15/05/2026")
   - **Time**: In HH:MM format (e.g., "09:00")
   - **Duration**: In minutes (e.g., 120 for 2 hours)
   - **Max Marks**: Total marks for the exam (e.g., 100)
   - **Venue**: Building or room info (e.g., "Main Campus, Building A")

### Step 5: Enroll Students in Exam Sections
**Menu Option: 25**

1. Select the department
2. Enter the section ID
3. Enter the student ID to enroll

**Note**: Students must be registered in the system before enrollment.

### Step 6: View Department Exam Schedule
**Menu Option: 26**

1. Select the department
2. Displays:
   - Exam schedule information
   - All exam sections in the schedule
   - Section details (invigilator, room, capacity, enrolled count)

### Step 7: View Exam Section Details
**Menu Option: 27**

1. Select the department
2. Enter the section ID
3. Displays:
   - Section information (capacity, enrollment, status)
   - Complete exam schedule for the section
   - List of enrolled students

## Exam Types Explained

### Midterm Exam
- Mid-semester assessment
- Typically 50-75% of the course evaluation
- Duration: Usually 1.5 to 2 hours

### Final Exam
- End-of-semester comprehensive assessment
- Often weighted heavily in final grades
- Duration: 2-3 hours

### Quiz
- Short assessment for topic mastery
- Lower weightage in final evaluation
- Duration: 15-45 minutes

### Assignment
- Coursework submission
- Can be individual or group project
- Variable duration based on complexity

## Sample Workflow

### Example 1: Setting up Computer Science Midterm Exams

```
1. Initialize Schedule (Option 22)
   - Department: Computer Science
   - Semester: Spring 2024
   
2. Create Sections (Option 23)
   - Section ID: CS_S1
   - Section Name: CS Midterm Section A
   - Invigilator: Mrs Precious Legodi
   - Room: A101
   - Capacity: 40

3. Add Exams (Option 24)
   - Exam ID: CSMID0
   - Exam Name: Data Structures
   - Exam Type: Midterm
   - Date: 15/05/2026
   - Time: 09:00
   - Duration: 120
   - Max Marks: 100
   - Venue: Main Campus

4. Enroll Students (Option 25)
   - Section: CS_S1
   - Student IDs: STU001, STU002, STU003, etc.

5. View Schedule (Option 26)
   - See all CS sections and exams
```

## Important Notes

1. **Student Registration**: Students must be registered in the system before they can be enrolled in exam sections.

2. **Capacity Management**: Sections have maximum capacity limits. 

3. **Duplicate Prevention**: The system prevents duplicate student enrollments in the same section.

4. **Memory Management**: The system properly manages all dynamically allocated memory for exams and sections.

5. **Data Validation**: The system validates:
   - Department exists
   - Schedule exists before creating sections
   - Section exists before adding exams or enrolling students

## Error Handling

### Common Messages:

- **"No exam schedule found for this department"** → Initialize a schedule first 
- **"Section is full! Cannot enroll more students"** → Section capacity exceeded
- **"Student is already enrolled in this section"** → Prevent duplicate enrollment
- **"Student not found!"** → Register student before enrollment
- **"Invalid choice!"** → Department number out of range


## File Structure

```
Exam/
├── Exam.h
├── Exam.cpp
├── ExamSection.h
├── ExamSection.cpp
├── ExamSchedule.h
└── ExamSchedule.cpp
```

## Integration with Other Features

The Exam Sections feature integrates seamlessly with:
- **Student Management**: Students must be registered before exam enrollment
- **Faculty Management**: Faculty can be invigilators
- **Department Management**: Each department has its own exam schedule
- **Academic Admin**: Can be extended to track student exam performance


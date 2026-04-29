#!/bin/bash

# Comprehensive test script for the University Management System
# This script tests all the new features added

echo "=========================================="
echo "University Management System - Test Suite"
echo "=========================================="
echo ""

# Create a test input file with various operations
cat > /tmp/test_input.txt << 'EOF'
1
STU001
John Doe
john.doe@university.edu
0795551234
CS2024001
1
2
3
4
STU002
Jane Smith
jane.smith@university.edu
0795551235
CS2024002
1
2
7
FAC001
Dr. Robert Johnson
robert.johnson@university.edu
0795556789
EMP001
1
1
75000
8
9
1
7
FAC002
Prof. Sarah Williams
sarah.williams@university.edu
0795556790
EMP002
2
2
65000
8
10
EMP001
Data Structures
10
EMP002
Database Systems
11
12
13
1
14
15
STU001
1
16
17
18
EOF

# Run the system with the test input
echo "Running University Management System with automated test cases..."
echo ""
echo "========== TEST LOG =========="
./university_system < /tmp/test_input.txt > /tmp/test_output.txt 2>&1

# Check if key features are present in the output
echo ""
echo "========== VERIFICATION RESULTS =========="
echo ""

# Check for student registration
if grep -q "Student Details:" /tmp/test_output.txt; then
    echo " Student Registration - PASSED"
else
    echo " Student Registration - FAILED"
fi

# Check for student viewing
if grep -q "REGISTERED STUDENTS LIST" /tmp/test_output.txt; then
    echo " View All Students - PASSED"
else
    echo " View All Students - FAILED"
fi

# Check for student search
if grep -q "SEARCH STUDENT" /tmp/test_output.txt; then
    echo " Search Student - PASSED"
else
    echo "✗ Search Student - FAILED"
fi

# Check for faculty addition
if grep -q "FACULTY MANAGEMENT" /tmp/test_output.txt || grep -q "Faculty member" /tmp/test_output.txt; then
    echo " Add Faculty - PASSED"
else
    echo " Add Faculty - FAILED"
fi

# Check for faculty viewing
if grep -q "ALL FACULTY MEMBERS" /tmp/test_output.txt; then
    echo " View All Faculty - PASSED"
else
    echo " View All Faculty - FAILED"
fi

# Check for course-faculty mapping
if grep -q "COURSE-FACULTY MAPPING" /tmp/test_output.txt || grep -q "assigned to course" /tmp/test_output.txt; then
    echo " Course-Faculty Mapping - PASSED"
else
    echo " Course-Faculty Mapping - FAILED"
fi

# Check for payroll feature
if grep -q "PAYROLL" /tmp/test_output.txt || grep -q "Monthly Payroll" /tmp/test_output.txt; then
    echo " Faculty Payroll - PASSED"
else
    echo " Faculty Payroll - FAILED"
fi

# Check for department display
if grep -q "DEPARTMENTS" /tmp/test_output.txt; then
    echo " View Departments - PASSED"
else
    echo " View Departments - FAILED"
fi

# Check for residence occupancy
if grep -q "RESIDENCE OCCUPANCY" /tmp/test_output.txt; then
    echo " Residence Occupancy - PASSED"
else
    echo " Residence Occupancy - FAILED"
fi

echo ""
echo "========== SYSTEM OUTPUT EXCERPT =========="
tail -50 /tmp/test_output.txt
echo ""
echo "========== TEST COMPLETE =========="
echo "Full output saved to: /tmp/test_output.txt"

# UNIVERSITY-MANAGEMENT-SYSTEM
A comprehensive object-oriented C++ system for managing university operations including student registration, faculty management, academic administration, and student residence management.

## Project Structure

### Classes Overview

```
Person (Base Class)
|___Student
|___Faculty

Department
-> Computer Science
-> Electronics
-> Mathematics
-> Physics
-> Statistics
-> Engineering
-> Information Technology
-> Cybersecurity

Adiministration
AcademicAdin
Residence
```

### 1. **Person** (Base Class)
- **Purpose**: Base class for all individuals in the university
-  **Attributes**: 
  - `id`, `name`, `email`, `phone`
- **Methods**:
  - Getters/Setters for all attributes
  - `displayInfo()` - Virtual method for displaying information




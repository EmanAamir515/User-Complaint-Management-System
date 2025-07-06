# User-Complaint-Management-System
Data Structures Project

Implemented in C++ using advanced data structures like **AVL Trees, Hash Tables, Doubly Linked Lists (DLL), Singly Linked Lists (SLL), and Priority Queues**. This project was developed as part of my Semester 3 coursework and served as a deep dive into efficient data organization and retrieval.

## **Features**
1. **User Management**  
   - Insert, search, and delete users by **ID, name, email, country, or type**.
   - Supports indexing via **AVL Trees (for names/emails) and Hash Tables (for IDs)**.
   - Group users by **country** (linear probing) or **type** (quadratic probing).

2. **Complaint Handling**  
   - Priority-based complaint registration (platinum/gold/silver tiers).
   - Max-heap to service high-priority complaints first.
   - Track complaints by user or country.

3. **Efficient Data Structures**  
   - **AVL Trees**: O(log n) search for names/emails.  
   - **Hash Tables**: O(1) average-case lookup for IDs.  
   - **DLL/SLL**: Flexible user and complaint storage.  
   - **Priority Queue**: Processes complaints by urgency.


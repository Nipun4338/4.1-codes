clear screen;

DROP TABLE Emp CASCADE CONSTRAINTS;

CREATE TABLE Emp (
	eid int, 
	ename varchar2(30), 
	age int, 
	designation varchar2(30));

	
SET VERIFY OFF;
SET SERVEROUTPUT ON;

DECLARE
	A Emp.eid%TYPE;
	B Emp.ename%TYPE;
	C Emp.age%TYPE;
	X Emp.eid%TYPE;

BEGIN
	DBMS_OUTPUT.PUT_LINE('Enter number of rows to insert: ');
	X:=&X;
	DBMS_OUTPUT.PUT_LINE('Enter Eid, ename, age: ');
	A:=&A;
	B:='&B';
	C:=&C;

	
	for i in 1..X LOOP
		CASE
			WHEN C>=50 THEN
				DBMS_OUTPUT.PUT_LINE('Employee is Most-Senior.');
				Insert into Emp (eid, ename, age, designation) values (A, B, C, 'Most-Senior');
			WHEN C<50 and C>=30 THEN
				DBMS_OUTPUT.PUT_LINE('Employee is Senior.');
				Insert into Emp (eid, ename, age, designation) values (A, B, C, 'Senior');
			ELSE
				DBMS_OUTPUT.PUT_LINE('Employee is Junior.');
				Insert into Emp (eid, ename, age, designation) values (A, B, C, 'Junior');
		END CASE;
	END LOOP;
END;
/
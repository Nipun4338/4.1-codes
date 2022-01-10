SET VERIFY OFF;
SET SERVEROUTPUT ON;

DECLARE
	A money.ID%TYPE;
	B money.NAME%TYPE;
	C money.taka%TYPE;

BEGIN
	A:=&A;
	B:='&B';
	C:=&C;
	
	For i in 1..5 LOOP
		INSERT into MONEY(ID,NAME,TAKA) VALUES(A, B, C);
		A:=A+1;c
	END LOOP;
END;
/
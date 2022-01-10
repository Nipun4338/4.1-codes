clear screen;

DROP TABLE Emp CASCADE CONSTRAINTS;
DROP TABLE Works CASCADE CONSTRAINTS;
DROP TABLE Dept CASCADE CONSTRAINTS;

CREATE TABLE Emp (
	eid int, 
	ename varchar2(30), 
	age int, 
	salary REAL);

CREATE TABLE Works (
	eid int, 
	did int, 
	pct_time int);

CREATE TABLE Dept (
	did int, 
	dname varchar2(30), 
	budget REAL, 
	managerid int);
	
Insert into Emp (eid, ename, age, salary) values (1, 'Robin', 25, 24000000);
Insert into Emp (eid, ename, age, salary) values (2, 'Rakib', 28, 30000);
Insert into Emp (eid, ename, age, salary) values (3, 'Sakib', 30, 40000);
Insert into Emp (eid, ename, age, salary) values (4, 'Tamim', 24, 21000);
Insert into Emp (eid, ename, age, salary) values (5, 'Ramim', 23, 24000);

Insert into Works (eid, did, pct_time) values (1, 1, 100);
Insert into Works (eid, did, pct_time) values (2, 1, 50);
Insert into Works (eid, did, pct_time) values (2, 2, 50);
Insert into Works (eid, did, pct_time) values (3, 2, 100);
Insert into Works (eid, did, pct_time) values (4, 4, 100);
Insert into Works (eid, did, pct_time) values (5, 3, 100);

Insert into Dept (did, dname, budget, managerid) values (1, 'SQA', 7500000, 1);
Insert into Dept (did, dname, budget, managerid) values (2, 'Finance', 5400000, 2);
Insert into Dept (did, dname, budget, managerid) values (3, 'Security', 1000001, 3);
Insert into Dept (did, dname, budget, managerid) values (4, 'Design', 7500000, 3);

Select ename, did, dname from Emp inner join Works On Emp.eid=Works.eid inner join Dept On 
Works.did=Dept.did where Emp.salary>Dept.budget;

Select managerid, sum(budget) from Dept group by managerid order by sum(budget) desc;

Select Emp.ename, d.managerid from Emp inner join Works On Emp.eid=Works.eid inner join Dept d On 
Works.did=d.did where EXISTS(select null from dept where Dept.budget>1000000 and Dept.budget<5000000 and Dept.managerid=d.managerid) and d.budget>1000000 order by d.managerid;
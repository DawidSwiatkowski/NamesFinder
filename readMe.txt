Problem:

	Z podanych przez użytkownika liter, należy ułożyć imiona z bazy imion (od 3 do 10 imion), tak by żadna litera nie pozostała.
	Litery mogą być wymienne z następujących baz:

	1. JS
	2. BKT
	3. CL
	4. MDV
	5. NW
	6. XS
	7. PGY
	8. HQZ
	9. RI
	10. A
	11. E
	12. O
	13. U

	K może być zamienne również na C (Kate, Cate).


Rozwiązanie:
	Wartość zbioru niech będzie miejscem w liczbie szesnastkowej, a ilość liter z danego zbioru będzie wartością.

	Np.
	Litery BAA to reprezentacja liczby : 0x12 (1 razy B, 2 razy A)
	Litery MBAAAAAAAAAAAAAAAA to liczba: 0x101F (16 A - to max)

	Z wszystkich liter z baz tworzymy sumy, każdy z każdym.
	Wyszukujemy liczbę stworzoną z podanych liter i kombinacji imion.


 
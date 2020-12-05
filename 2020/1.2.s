.globl main
.text
main:
    la $s0 numbers
    li $s1 800   # numbers length in bytes
    li $s2 0     # i
    li $s3 2020  # target sum

outer_loop:
    # while i < numbers length
    beq $s2 $s1 exit

    # t0 = numbers[i++]
    add $t0 $s2 $s0
    lw $t0 ($t0)
    addi $s2 $s2 4

    li $s4 0  # j

middle_loop:
    # while j < numbers length
    beq $s4 $s1 outer_loop

    # t1 = numbers[j++]
    add $t1 $s4 $s0
    lw $t1 ($t1)
    addi $s4 $s4 4

    li $s5 0  # k

inner_loop:
    # while k < numbers length
    beq $s5 $s1 middle_loop

    # t2 = numbers[k++]
    add $t2 $s5 $s0
    lw $t2 ($t2)
    addi $s5 $s5 4

    # if numbers[i] + numbers[j] +
    #    numbers[k] != target sum
    add $t3 $t0 $t1
    add $t4 $t2 $t3
    bne $s3 $t4 inner_loop  # continue k loop

    # result = numbers[i] * 
    #          numbers[j] * numbers[k]
    mul $t3 $t0 $t1
    mul $t3 $t3 $t2
    
    # print result
    move $a0 $t3
    li $v0 1
    syscall
    li $a0 10
    li $v0 11
    syscall

exit:
    li $v0 10
    syscall

.data  
numbers: .word 1597 1857 1703 1956 1809 1683 1629 230 1699 1875 1564 1700 1911 1776 1955 1585 1858 1725 1813 1568 1962 1535 487 1621 1620 1573 1918 1794 2003 1957 1840 1936 285 1630 1753 1649 1951 1968 1916 1694 1593 1980 1806 1779 1637 1674 1842 1659 1553 1846 1677 1944 1811 1645 1784 1791 1988 1864 1596 1773 1132 1715 1938 1901 1617 1892 1708 1788 1765 1684 1595 1971 1798 1543 507 1772 1757 1950 1844 1898 1671 1602 1599 1524 2005 1855 1624 1884 1990 1604 1873 1736 1747 1900 1534 1713 1690 1525 1838 587 74 1979 1635 1896 1580 1727 1994 1940 1819 1758 1852 1639 1754 1559 1919 1879 1874 1921 1575 1693 1710 1949 1719 1933 1673 1909 1989 1897 909 1889 1641 1658 1530 1541 1952 1627 1839 1803 833 1527 1756 2009 1605 1548 1660 1966 1770 1552 1939 1726 382 1665 1960 1733 1983 1544 1974 1985 1625 609 1931 1749 1975 1562 1563 1922 2008 2010 1704 1545 1636 1762 1841 1717 622 2007 1670 1771 1910 1978 1615 1805 1999 1643 1748 1531 1539 1787 1722 1111 1774 1540 1607 1902 1991 1763 1691 1812 1783 1579


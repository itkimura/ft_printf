make ft_printf
make printf
./ft_printf > ft_printf.txt
./printf > printf.txt
echo ""
echo "[ft_printf]"
cat -e ft_printf.txt
echo ""
echo "[printf]"
cat -e printf.txt
echo ""
echo "[diff]"
diff -a --suppress-common-lines ft_printf.txt printf.txt
echo ""
make clean
rm ft_printf.txt printf.txt

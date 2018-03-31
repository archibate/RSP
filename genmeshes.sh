gen() {
	echo gen $1 $2
	(python cylinder-gen.py $1 yes &&
	 python material-gen.py grey70 ) > cylinder$2.mesh
	(python cone-gen.py $1 yes &&
	 python material-gen.py grey70 ) > cone$2.mesh
	(python cone-gen.py $1 no &&
	 python material-gen.py grey30 ) > nobot-cone$2.mesh
	(python thruster-gen.py $1 0.65 &&
	 python material-gen.py grey30 ) > thruster$2.mesh
}

med=${1-20}
low=$(($med / 2))
high=$(($med * 2))

gen $med
gen $low -lp
gen $high -hp

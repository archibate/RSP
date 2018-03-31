cylnprec=${1-20}
(python cylinder-gen.py $cylnprec yes
python material-gen.py wall ) > cylinder.mesh
(python cone-gen.py $cylnprec yes
python material-gen.py wall ) > cone.mesh
(python cone-gen.py $cylnprec no
python material-gen.py grey55 ) > nobot-cone.mesh
(python thruster-gen.py $cylnprec 0.65
python material-gen.py grey55 ) > thruster.mesh

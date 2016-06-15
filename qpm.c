#include <stdio.h>


int main()
{
     struct subparticle {
            float pos[3], vel[3], rho;
        };

        struct FileHeader {
            int         npart, npsh, nstar;
            float       aa, softlen;
        } header;

        FILE * fp;
        fp = fopen('/',"rb")


        int eflag, hsize;
        fread(&eflag, sizeof(int),1,fp);
        fread(&hsize, sizeof(int),1,fp);
        fread(&header, sizeof(struct FileHeader),1,fp);
        int nobj=header.npart;

        struct subparticle * P;
        P = (struct subparticle*) malloc (nobj);

// Read the position
        std::vector<float> buff;
        buff = (float *) malloc (3*nobj);
        fread(&buff[0],sizeof(float),3*nobj,fp);

        for (int nn=0; nn<nobj; ++nn) {
            for (int idim=0; idim<3; ++idim) {
                P[ntotal+nn].pos[idim] = fbuf[3*nn+idim];
            }
        }

//Read the velocity

        fread(&buff[0],sizeof(float),3*nobj,fp);

        for (int nn=0; nn<nobj; ++nn) {
            for (int idim=0; idim<3; ++idim) {
                P[ntotal+nn].vel[idim] = fbuf[3*nn+idim];
            }
        }

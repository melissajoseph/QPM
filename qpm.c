#include <stdio.h>
#include <stdlib.h> 


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
                P[nn].pos[idim] = fbuf[3*nn+idim];
            }
        }

//Read the velocity

        fread(&buff[0],sizeof(float),3*nobj,fp);

        for (int nn=0; nn<nobj; ++nn) {
            for (int idim=0; idim<3; ++idim) {
                P[nn].vel[idim] = fbuf[3*nn+idim];
            }
        }
        
//Read the density        
     float rhomin=1e30, rhomax=-1e30;
     fread(&buff[0],sizeof(float),nobj,fp);

     for (int nn=0; nn<nobj; ++nn) {
          float d_in = buff[nn];
          float d_out;
          d_out = sqrt(
                           (RhoClip*RhoClip) * (d_in*d_in)
                         /
                           ( RhoClip*RhoClip + d_in*d_in  )
                        );
          if (d_out < rhomin) rhomin=d_out;
          if (d_out > rhomax) rhomax=d_out;

          P[nn].rho = d_out;
        }
        printf("Rhomin,Rhomax %4.2f %4.2f \n",rhomin,rhomax);
        printf("Number of particles %d \n", nobj);
        fclose(fname);
        return 0;

}


double selectprob(const float rho) {
double prob;
double mu=1.0;
if (rho>0){
double x = (log(rho)-mu)/0.1;
prob = exp(-0.5*x*x);
}
else {
prob = 0.0;
}
return(prob);
}


struct subparticle select_sample(double nbar, struct subparticle P)  {

double navg=0, ntot=0,norm;
long size = P.size();
struct subparticle *tmp;
     tmp = (struct subparticle*) malloc (nbar)
int nn;
for (int nn=0; nn < size; ++nn) {
     double p = P[nn].wt * selectprob(P[nn].rho);
     if (p > maxprob) maxprob=p;
          navg += p;
          ntot += P[nn].wt;
     }

norm = nbar/navg;
int c = 0;
struct subparticle Ptmp;
          Ptmp = (struct subparticle*) malloc (1);
for (int nn=0; nn<size; ++nn) {
     double r = drand48();
     double prob = norm * P[nn].wt * this->model.selectprob(P[nn].rho) * P[nn].exclude;
     
     if((r < prob)) {
          c += 1;
          for (int idim=0; idim<3; ++idim) {
               Ptmp.pos[idim] = P[nn].pos[idim];
               Ptmp.vel[idim] = P[nn].vel[idim];
                    }
          tmp[c] = Ptmp;
     }

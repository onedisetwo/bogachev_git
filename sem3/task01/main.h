# ifndef M
# define M 10
# endif

#define LEN (1234)

# ifndef data_H
# define data_H
# include <stdio.h>
#include <string.h>

class data{
	private:
		int m = M;
		double a[M] = {};
		static int p;
	public:
		data () = default;
		~data () = default;
		int get_m () const { return m; }
		int get_M () const { return (m < M ? m : M); }
		const double * get_a () { return a; }
		static int get_p () { return p; }
		static void set_p (int q){
			p = q;
		}
		data (const data &x) = default;
		data& operator= (const data&) = default;
		int operator< (const data& x) const{
			return m < x.m;
		}
		int operator> (const data& x) const{
			return m > x.m;
		}
		// Print data in a line (not more than p): m a[0] a[1] ... a[m-1]
		void print (FILE* fp = stdout) const;
		// Read data from the line: m a[0] a[1] ... a[m-1]
		int read (FILE* fp = stdin);
		// Init data by formulae with number s
		void init (int s, int n, int i);
};

# endif // data

int f (int s, int n, int i);
int read_array (data* data_m, int n, char* filename);
void print_array (data* data_m, int n, int p);
void init_array (data* data_m, int n, int s);

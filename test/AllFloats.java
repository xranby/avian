public class AllFloats {
  private static float multiplyByFive(float a) {return 5f * a;}
  private static double multiplyByFive(double a) {return 5d * a;}
  private static float multiply(float a, float b) {return a * b;}
  private static double multiply(double a, double b) {return a * b;}
  private static double multiply(float a, double b) {return a * b;}
  private static float divide(float a, float b) {return a / b;}
  private static double divide(double a, double b) {return a / b;}
  private static double divide(float a, double b) {return a / b;}
  private static float remainder(float a, float b) {return a % b;}
  private static double remainder(double a, double b) {return a % b;}
  private static double remainder(float a, double b) {return a % b;}
  private static float add(float a, float b) {return a + b;}
  private static double add(double a, double b) {return a + b;}
  private static double add(float a, double b) {return a + b;}
  private static float subtract(float a, float b) {return a - b;}
  private static double subtract(double a, double b) {return a - b;}
  private static double subtract(float a, double b) {return a - b;}
  private static float complex(float a, float b) {return (a - b) / (a * b) + (float)Math.sqrt(a);}
  private static double complex(double a, double b) {return (a - b) / (a * b) + Math.sqrt(a);}
  private static double complex(float a, double b) {return (a - b) / (a * b) + Math.sqrt(a);}
  private static double sqrt(double a) {return Math.sqrt(a);}
  private static float complexNoIntrinsic(float a, float b) {return (a - b) / (a * b) + (float)sqrt(a);}
  private static int f2i(float a) {return (int)a;}
  private static long f2l(float a) {return (long)a;}
  private static float i2f(int a) {return (float)a;}
  private static double i2d(int a) {return (double)a;}
  private static int d2i(double a) {return (int)a;}
  private static long d2l(double a) {return (long)a;}
  private static float l2f(long a) {return (float)a;}
  private static double l2d(long a) {return (double)a;}
  private static float negate(float a) {return -a;}
  private static double negate(double a) {return -a;}
  private static int abs(int a) {return Math.abs(a);}
  private static float abs(float a) {return Math.abs(a);}
  
  private static void expect(boolean v) {
    if(!v)throw new RuntimeException();
  }

  private static void expectEqual(double expected, double found) {
    if(expected != found) {
      throw new RuntimeException("expected: " + expected + " found: " + found);
    }
  }
  
  private static int last(){return 0;}
  
  public static void main(String[] args) {
    expectEqual(5f * 36f, multiplyByFive(36f));

    expectEqual(5d*36d, multiplyByFive(36d));
    expectEqual(5f*4f, multiply(5f, 4f));
    expectEqual(5d*4d, multiply(5d, 4d));
    expectEqual(5f*4d, multiply(5f, 4d));
    expectEqual(5f/2f, divide(5f, 2f));
    expectEqual(5d/2d, divide(5d, 2d));
    expectEqual(5f/2d, divide(5f, 2d));

    expectEqual(5f%2f, remainder(5f, 2f));

    expectEqual(5f%2f, remainder(5f, 2f));
    expectEqual(5d%2d, remainder(5d, 2d));
    expectEqual(5f%2d, remainder(5f, 2d));
    expectEqual(5f+4f, add(5f, 4f));
    expectEqual(5f+4d, add(5d, 4d));
    expectEqual(5f+4d, add(5f, 4d));
    expectEqual(5f-4f, subtract(5f, 4f));
    expectEqual(5f-4d, subtract(5d, 4d));
    expectEqual(5f-4d, subtract(5f, 4d));
    expectEqual((4f-3f)/(4f*3f) + 2f, complex(4f, 3f));
    expectEqual((4d-3d)/(4d*3d) + 2d, complex(4d, 3d));
    expectEqual((4f-3d)/(4f*3d) + 2f, complex(4f, 3d));
    expectEqual((4f-3f)/(4f*3f) + 2f, complexNoIntrinsic(4f, 3f));
    
    expectEqual( 4, f2i(4f));
    expectEqual( 4, f2l(4f));
    expectEqual( 4f, i2f(4));
    expectEqual( 4d, i2d(4));
    
    expectEqual( 4, d2i(4d));
    expectEqual( 4, d2l(4d));
    expectEqual( 4f, l2f(4));
    expectEqual( 4d, l2d(4));

    expectEqual(-4f, negate(4f));
    expectEqual(-4d, negate(4d));
    
    expectEqual( 4, abs(-4));
    expectEqual( 12, abs(12));
    expectEqual( 4f, abs(-4f));
    expectEqual( 12f, abs(12f));
    
    int unused = last();
  }
}

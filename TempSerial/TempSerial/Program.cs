using System;
using System.IO.Ports;
using System.Text;

namespace ArduinoSerial_DataToCSV
{
    class Program
    {
        static void Main(string[] args)
        {
            //キー入力に使用
            var outChar = "";

            foreach (var portName in SerialPort.GetPortNames())
            {
                Console.WriteLine(portName);
            }

            //現在時刻
            DateTime dt = DateTime.Now;
            String now_time = dt.ToString();
            now_time = now_time.Replace("/", ".").Replace(" ", "_").Replace(":", "-");

            String PATH = now_time + "_SensorData.csv";

            //EncodeをShift-Jisに対応
            Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);

            //シリアルポート取得
            SerialPort sp = new SerialPort("COM8");
            sp.BaudRate = 9600;
            sp.Parity = Parity.None;
            sp.DataBits = 8;
            sp.StopBits = StopBits.One;
            sp.Handshake = Handshake.None;
            sp.Open();

            //csv出力
            var sw = new System.IO.StreamWriter(PATH, false, System.Text.Encoding.GetEncoding("shift_jis"));

            //Arduino側のサンプリング周波数


            while (true)
            {
                //センサ値1行分取得
                string data = sp.ReadLine();

                //csv出力
                sw.WriteLine(data);
                Console.WriteLine(data);
                sw.Flush();

                //Q入力でプログラム終了
                if (Console.KeyAvailable)
                {
                    outChar = Console.ReadKey().Key.ToString();
                    if (outChar == "Q")
                    {
                        return;
                    }
                }

            }
        }
    }
}
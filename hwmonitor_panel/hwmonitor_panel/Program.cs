using System;
using OpenHardwareMonitor.Hardware;
using System.IO.Ports;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;

namespace hwmonitor_panel
{
    class Program
    {
        /**
         *  Define vars to hold stats
         **/

        // CPU Temp
        static float cpuTemp;
        // CPU Usage
        static float cpuUsage;
        // CPU Power Draw (Package)
        static float cpuPowerDrawPackage;
        // CPU Frequency
        static float cpuFrequency;
        // GPU Temperature
        static float gpuTemp;
        // GPU Usage
        static float gpuUsage;
        // GPU Core Frequency
        static float gpuCoreFrequency;
        // GPU Memory Frequency
        static float gpuMemoryFrequency;
        // RAM Memory Usage
        static float ramUsage;
        // HDD Temperature
        static float hddTemp;
        // HDD Usage
        // List to store HDD usages
        static List<float> hddUsages = new List<float>();

        // Serial Port
        static SerialPort serialPort;

        // UDP Client
        static UdpClient udpClient;
        static IPEndPoint udpEndPoint;

        /**
         * Init OpenHardwareMonitor.dll Computer Object
         **/

        static Computer c = new Computer()
        {
            GPUEnabled = true,
            CPUEnabled = true,
            RAMEnabled = true, // uncomment for RAM reports
            //MainboardEnabled = true, // uncomment for Motherboard reports
            //FanControllerEnabled = true, // uncomment for FAN Reports
            HDDEnabled = true, // uncomment for HDD Report
        };

        /**
         * Initialize Serial Port
         **/
        static void InitializeSerialPort()
        {
            serialPort = new SerialPort("COM8", 115200, Parity.None, 8, StopBits.One);
            serialPort.Open();
        }

        /**
         * Initialize UDP Client
         **/
        static void InitializeUdpClient()
        {
            Console.Write("Enter the IP address: ");
            string ipAddress = Console.ReadLine();

            Console.Write("Enter the port number: ");
            string portInput = Console.ReadLine();
            int port;

            // Validate port input
            while (!int.TryParse(portInput, out port) || port <= 0 || port > 65535)
            {
                Console.WriteLine("Invalid port number. Please enter a valid port (1-65535): ");
                portInput = Console.ReadLine();
            }

            udpClient = new UdpClient();

            try
            {
                udpEndPoint = new IPEndPoint(IPAddress.Parse(ipAddress), port);
                Console.WriteLine($"UDP Client initialized with IP {ipAddress} and port {port}");
            }
            catch (FormatException)
            {
                Console.WriteLine("Invalid IP address format.");
            }
        }   

    /**
     * Send data over Serial Port
     **/
    static void SendSerialData()
        {
            //string data = $"{cpuTemp:F2},{cpuUsage:F2},{cpuPowerDrawPackage:F2},{cpuFrequency:F2}," +

            //               $"{gpuTemp:F2},{gpuUsage:F2},{gpuCoreFrequency:F2},{gpuMemoryFrequency:F2}";
            //string data = $"{cpuTemp}|{cpuUsage}|{cpuPowerDrawPackage}|{cpuFrequency}|" +
            //   $"{gpuTemp}|{gpuUsage}|{gpuCoreFrequency}|{gpuMemoryFrequency}";

            // Convert floats to integers
            int cpuTempInt = (int)Math.Round(cpuTemp);
            int cpuUsageInt = (int)Math.Round(cpuUsage);
            int cpuPowerDrawPackageInt = (int)Math.Round(cpuPowerDrawPackage);
            int cpuFrequencyInt = (int)Math.Round(cpuFrequency);
            int gpuTempInt = (int)Math.Round(gpuTemp);
            int gpuUsageInt = (int)Math.Round(gpuUsage);
            int gpuCoreFrequencyInt = (int)Math.Round(gpuCoreFrequency);
            int gpuMemoryFrequencyInt = (int)Math.Round(gpuMemoryFrequency);

            string data = $"{cpuTempInt}|{cpuUsageInt}|{cpuPowerDrawPackageInt}|{cpuFrequencyInt}|" +
                           $"{gpuTempInt}|{gpuUsageInt}|{gpuCoreFrequencyInt}|{gpuMemoryFrequencyInt}";


            try
            {
                if (serialPort.IsOpen)
                {
                    Console.WriteLine($"Send Serial packet: {data}");
                    serialPort.WriteLine(data);
                }
                else
                {
                    Console.WriteLine("Serial port is not open.");
                    InitializeSerialPort();
                }
            }
            catch (UnauthorizedAccessException ex)
            {
                Console.WriteLine($"Access to the port is denied: {ex.Message}");
            }
            catch (InvalidOperationException ex)
            {
                Console.WriteLine($"The specified port is not open: {ex.Message}");
            }
            catch (System.IO.IOException ex)
            {
                Console.WriteLine($"I/O error while communicating with the port: {ex.Message}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An unexpected error occurred: {ex.Message}");
            }
        }

        /**
         * Send data over UDP
         **/
        static void SendUdpData()
        {
            // Convert floats to integers
            int cpuTempInt = (int)Math.Round(cpuTemp);
            int cpuUsageInt = (int)Math.Round(cpuUsage);
            int cpuPowerDrawPackageInt = (int)Math.Round(cpuPowerDrawPackage);
            int cpuFrequencyInt = (int)Math.Round(cpuFrequency);
            int gpuTempInt = (int)Math.Round(gpuTemp);
            int gpuUsageInt = (int)Math.Round(gpuUsage);
            int gpuCoreFrequencyInt = (int)Math.Round(gpuCoreFrequency);
            int gpuMemoryFrequencyInt = (int)Math.Round(gpuMemoryFrequency);
            int ramUsageInt = (int)Math.Round(ramUsage);
            int hddTempInt = (int)Math.Round(hddTemp);

            string data = $"{cpuTempInt}|{cpuUsageInt}|{cpuPowerDrawPackageInt}|{cpuFrequencyInt}|" +
                           $"{gpuTempInt}|{gpuUsageInt}|{gpuCoreFrequencyInt}|{gpuMemoryFrequencyInt}|" +
                           $"{ramUsageInt}|";

            // Now, you have all HDD usages in the hddUsages list
            for (int i = 0; i < hddUsages.Count; i++)
            {
                int hddUsageInt = (int)Math.Round(hddUsages[i]);
                data += $"{hddUsageInt}";

                // Add the separator only if it's not the last item
                if (i < hddUsages.Count - 1)
                {
                    data += "|";
                }
            }
            // Clear the hddUsages list
            hddUsages.Clear();

            Console.WriteLine($"Send UDP packet: {data}");

            byte[] dataBytes = System.Text.Encoding.UTF8.GetBytes(data);
            udpClient.Send(dataBytes, dataBytes.Length, udpEndPoint);
        }

        /**
         * Pulls data from OHM
         **/

        static void ReportSystemInfo()
        {
            Console.WriteLine("---");
            foreach (var hardware in c.Hardware)
            {

                if (hardware.HardwareType == HardwareType.CPU)
                {
                    // only fire the update when found
                    hardware.Update();

                    // loop through the data
                    foreach (var sensor in hardware.Sensors)
                        if (sensor.SensorType == SensorType.Temperature && sensor.Name.Contains("CPU Package"))
                        {
                            // store
                            cpuTemp = sensor.Value.GetValueOrDefault();
                            // print to console
                            System.Diagnostics.Debug.WriteLine("cpuTemp: " + sensor.Value.GetValueOrDefault());
                            Console.WriteLine("cpuTemp: " + sensor.Value.GetValueOrDefault());
                        }
                        else if (sensor.SensorType == SensorType.Load && sensor.Name.Contains("CPU Total"))
                        {
                            // store
                            cpuUsage = sensor.Value.GetValueOrDefault();
                            // print to console
                            System.Diagnostics.Debug.WriteLine("cpuUsage: " + sensor.Value.GetValueOrDefault());
                            Console.WriteLine("cpuFrequency: " + sensor.Value.GetValueOrDefault());
                        }
                        else if (sensor.SensorType == SensorType.Power && sensor.Name.Contains("CPU Package"))
                        {
                            // store
                            cpuPowerDrawPackage = sensor.Value.GetValueOrDefault();
                            // print to console
                            System.Diagnostics.Debug.WriteLine("CPU Power Draw - Package: " + sensor.Value.GetValueOrDefault());
                            Console.WriteLine("cpuFrequency: " + sensor.Value.GetValueOrDefault());

                        }
                        else if (sensor.SensorType == SensorType.Clock && sensor.Name.Contains("CPU Core #1"))
                        {
                            // store
                            cpuFrequency = sensor.Value.GetValueOrDefault();
                            // print to console
                            System.Diagnostics.Debug.WriteLine("cpuFrequency: " + sensor.Value.GetValueOrDefault());
                            Console.WriteLine("cpuFrequency: " + sensor.Value.GetValueOrDefault());
                        }
                }


                // Targets AMD & Nvidia GPUS
                if (hardware.HardwareType == HardwareType.GpuAti || hardware.HardwareType == HardwareType.GpuNvidia)
                {
                    // only fire the update when found
                    hardware.Update();

                    // loop through the data
                    foreach (var sensor in hardware.Sensors)
                        if (sensor.SensorType == SensorType.Temperature && sensor.Name.Contains("GPU Core"))
                        {
                            // store
                            gpuTemp = sensor.Value.GetValueOrDefault();
                            // print to console
                            System.Diagnostics.Debug.WriteLine("gpuTemp: " + sensor.Value.GetValueOrDefault());
                            Console.WriteLine("gpuTemp: " + sensor.Value.GetValueOrDefault());
                        }
                        else if (sensor.SensorType == SensorType.Load && sensor.Name.Contains("GPU Core"))
                        {
                            // store
                            gpuUsage = sensor.Value.GetValueOrDefault();
                            // print to console
                            System.Diagnostics.Debug.WriteLine("gpuUsage: " + sensor.Value.GetValueOrDefault());
                            Console.WriteLine("gpuUsage: " + sensor.Value.GetValueOrDefault());
                        }
                        else if (sensor.SensorType == SensorType.Clock && sensor.Name.Contains("GPU Core"))
                        {
                            // store
                            gpuCoreFrequency = sensor.Value.GetValueOrDefault();
                            // print to console
                            System.Diagnostics.Debug.WriteLine("gpuCoreFrequency: " + sensor.Value.GetValueOrDefault());
                            Console.WriteLine("gpuCoreFrequency: " + sensor.Value.GetValueOrDefault());
                        }
                        else if (sensor.SensorType == SensorType.Clock && sensor.Name.Contains("GPU Memory"))
                        {
                            // store
                            gpuMemoryFrequency = sensor.Value.GetValueOrDefault();
                            // print to console
                            System.Diagnostics.Debug.WriteLine("gpuMemoryFrequency: " + sensor.Value.GetValueOrDefault());
                            Console.WriteLine("gpuMemoryFrequency: " + sensor.Value.GetValueOrDefault());
                        }
                }

                // ... you can access any other system information you want here

                // RAM
                if (hardware.HardwareType == HardwareType.RAM)
                {
                    // only fire the update when found
                    hardware.Update();

                    // loop through the data
                    foreach (var sensor in hardware.Sensors)
                        if (sensor.SensorType == SensorType.Load)
                        {
                            ramUsage = sensor.Value.GetValueOrDefault();
                            // print to console
                            System.Diagnostics.Debug.WriteLine("ramUsage: " + sensor.Value.GetValueOrDefault());
                            Console.WriteLine("ramUsage: " + sensor.Value.GetValueOrDefault());
                        }
                }

                // HDD
                if (hardware.HardwareType == HardwareType.HDD)
                {
                    // only fire the update when found
                    hardware.Update();

                    // loop through the data
                    foreach (var sensor in hardware.Sensors)
                        if (sensor.SensorType == SensorType.Load)
                        {
                            float hddUsage = sensor.Value.GetValueOrDefault();

                            // Store the usage into the list
                            hddUsages.Add(hddUsage);

                            // print to console
                            System.Diagnostics.Debug.WriteLine("hddUsage: " + sensor.Value.GetValueOrDefault());
                            Console.WriteLine(hardware.Name + " hddUsage: " + sensor.Value.GetValueOrDefault());
                        }
                }
            }
            Console.WriteLine("---");
        }

        /**
         * Clean up resources
         **/
        static void Cleanup()
        {
            if (serialPort != null && serialPort.IsOpen)
            {
                serialPort.Close();
                serialPort.Dispose();
            }
            if (udpClient != null)
            {
                udpClient.Close();
                udpClient.Dispose();
            }
            c.Close();
        }
        static void Main(string[] args)
        {
            // Handle application exit
            AppDomain.CurrentDomain.ProcessExit += (s, e) => Cleanup();
            Console.CancelKeyPress += (s, e) =>
            {
                e.Cancel = true; // Prevent the application from terminating immediately
                Cleanup();
                Environment.Exit(0); // Exit gracefully
            };

            // Initialize hardware monitor and serial port
            c.Open();
            //InitializeSerialPort();
            InitializeUdpClient();

            // loop
            while (true)
            {
                ReportSystemInfo();
                //SendSerialData();
                SendUdpData();
                System.Threading.Thread.Sleep(1000); // Sleep for 1 second before the next update
            }
        }
    }
}
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.NetworkInformation;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PingHost
{
    public partial class Form1 : Form
    {
        Ping pingSender;
        int timeout;
        List<PacketStatistic> packetsStatistics;

        public Form1()
        {
            InitializeComponent();

            pingSender = new Ping();
            timeout = 120;
            packetsStatistics = new List<PacketStatistic>();
        }

        private void buttonPing_Click(object sender, EventArgs e)
        {
            string hostName = textBoxHostName.Text;

            try
            {
                if (hostName.Length == 0) throw new PingException("Host name is null");

                PingReply reply = pingSender.Send(hostName, timeout);
            }
            catch (PingException)
            {
                MessageBox.Show(
                    "Host name is wrong!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            PacketStatistic packetStatistic = new PacketStatistic(hostName);
            packetsStatistics.Add(packetStatistic);

            Info();
        }

        private void Info()
        {
            listBoxInfo.Items.Clear();

            for (int i = 0; i < packetsStatistics.Count; i++) 
            {
                PacketStatistic packetStatistic = packetsStatistics[i];
                PingReply reply = pingSender.Send(packetStatistic.hostName, timeout);
                packetStatistic.transmittedCount++;

                string returnMessage;
                switch (reply.Status)
                {
                    case IPStatus.Success:
                        packetStatistic.receivedCount++;

                        returnMessage = string.Format(
                            "Reply from {0} ({1}): bytes={2}  time={3}ms  TTL={4}  Packets transmitted={5}  Packets loss={6}",
                            reply.Address,
                            packetStatistic.hostName,
                            reply.Buffer.Length,
                            reply.RoundtripTime,
                            reply.Options.Ttl,
                            packetStatistic.transmittedCount,
                            packetStatistic.transmittedCount - packetStatistic.receivedCount);
                        break;
                    case IPStatus.TimedOut:
                        returnMessage = string.Format(
                            "Reply from ({0}): Connection has timed out... Packets transmitted={1}  Packets loss={2}",
                            packetStatistic.hostName,
                            packetStatistic.transmittedCount,
                            packetStatistic.transmittedCount - packetStatistic.receivedCount);
                        break;
                    default:
                        returnMessage = string.Format("Ping failed: {0}", reply.Status.ToString());
                        break;
                }
                listBoxInfo.Items.Add(returnMessage);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Info();
        }
    }
}

class PacketStatistic
{
    public string hostName;
    public int transmittedCount;
    public int receivedCount;

    public PacketStatistic(string hostName)
    {
        this.hostName = hostName;
        transmittedCount = 0;
        receivedCount = 0;
    }
}
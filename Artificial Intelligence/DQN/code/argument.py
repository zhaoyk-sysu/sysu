def dqn_arguments(parser):
    parser.add_argument('--env_name', default="CartPole-v1", help='environment name')
    parser.add_argument('--train_dqn', action='store_true', help='whether train DQN')
    parser.add_argument('--test', action='store_true', help='whether test model')

    parser.add_argument("--seed", default=11037, type=int)
    parser.add_argument("--hidden_size", default=32, type=int)
    parser.add_argument("--lr", default=0.001, type=float)
    parser.add_argument("--gamma", default=0.9, type=float)
    parser.add_argument("--epsilon", default=0.2, type=float)
    parser.add_argument("--tau", default=1., type=float)

    parser.add_argument("--use_cuda", default=True, type=bool)
    parser.add_argument("--n_iter", default=5000, type=int)
    parser.add_argument("--max_episode_len", default=500, type=int)
    parser.add_argument("--update_step", default=4, type=int)
    parser.add_argument("--epsilon_decay", default=0.995, type=float)
    parser.add_argument("--epsilon_min", default=0.01, type=float)  
    parser.add_argument('--target_update_freq', type=int, default=1000, help='Frequency of target network update')
    parser.add_argument('--memory_capacity', type=int, default=10000, help='Replay buffer capacity')

    parser.add_argument("--batch_size", default=32, type=int)
    parser.add_argument('--save_path', type=str, default='./dqn_model.pth', help='模型保存路径')

    parser.add_argument("--log_path", default="./log/log.txt", type=str)
    parser.add_argument('--episodes', type=int, default=550, help='训练的总回合数')


    return parser
